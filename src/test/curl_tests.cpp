/**
 * Copyright (c) 2015-2018 COLX Developers
 * Copyright (c) 2018-2019 Galilel Developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "bootstrap/curl.h"
#include "util.h"

#include <string>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/operations.hpp>

BOOST_AUTO_TEST_SUITE(curl_tests)

BOOST_AUTO_TEST_CASE(curl_getredirect_test)
{
    std::string err1, out1;
    BOOST_CHECK(CURLGetRedirect("https://github.com/Limitless-VIP/Limitless/releases/latest", out1, err1));
    BOOST_CHECK_MESSAGE(err1.empty(), err1);
    BOOST_CHECK(!out1.empty());

    std::string err2, out2;
    BOOST_CHECK(!CURLGetRedirect("http://icanhazip.com", out2, err2));
    BOOST_CHECK(!err2.empty());
    BOOST_CHECK_MESSAGE(out2.empty(), out2);
}

BOOST_AUTO_TEST_CASE(curl_download_test)
{
    const CUrl url = "https://raw.githubusercontent.com/Limitless-VIP/Limitless/master/README.md";
    const std::string tmpFile(GetTempPath().string() + "/download.tmp");
    auto ProgressFn = [](double total, double now) { return 0; };
    std::string buff, err;

    {/** test with progress fn */
        BOOST_REQUIRE_MESSAGE(CURLDownloadToMem(url, ProgressFn, buff, err), err);
        BOOST_CHECK_MESSAGE(err.empty(), err);
        BOOST_REQUIRE_MESSAGE(CURLDownloadToFile(url, tmpFile, ProgressFn, err), err);
        BOOST_CHECK_MESSAGE(err.empty(), err);

        std::ifstream f(tmpFile, std::ios::binary);
        std::string filebuff((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        f.close();
        BOOST_CHECK(buff == filebuff);

        BOOST_REQUIRE(boost::filesystem::remove(tmpFile));
    }

    {/** test without progress fn */
        BOOST_REQUIRE_MESSAGE(CURLDownloadToMem(url, nullptr, buff, err), err);
        BOOST_CHECK_MESSAGE(err.empty(), err);
        BOOST_REQUIRE_MESSAGE(CURLDownloadToFile(url, tmpFile, nullptr, err), err);
        BOOST_CHECK_MESSAGE(err.empty(), err);

        std::ifstream f(tmpFile, std::ios::binary);
        std::string filebuff((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        f.close();
        BOOST_CHECK(buff == filebuff);

        BOOST_REQUIRE(boost::filesystem::remove(tmpFile));
    }

    /** test empty url */
    BOOST_CHECK(!CURLDownloadToMem("", nullptr, buff, err));
    BOOST_CHECK(!err.empty());
    BOOST_CHECK(!CURLDownloadToFile("", tmpFile, nullptr, err));
    BOOST_CHECK(!err.empty());

    /** test empty file */
    BOOST_CHECK(!CURLDownloadToFile(url, "", nullptr, err));
    BOOST_CHECK(!err.empty());

    /** test invalid url */
    BOOST_CHECK(!CURLDownloadToMem("invalid_url", nullptr, buff, err));
    BOOST_CHECK(!err.empty());
    BOOST_CHECK(!CURLDownloadToFile("invalid_url", tmpFile, nullptr, err));
    BOOST_CHECK(!err.empty());

    BOOST_REQUIRE(boost::filesystem::remove(tmpFile));
}

BOOST_AUTO_TEST_SUITE_END()
