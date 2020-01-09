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

#include "bootstrap/ziputil.h"
#include "util.h"
#include "utiltime.h"
#include "tinyformat.h"

#include <string>
#include <fstream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/operations.hpp>

static bool CompareFiles(const std::string& left, const std::string& right)
{
    std::ifstream f1(left), f2(right);
    std::string str1((std::istreambuf_iterator<char>(f1)), std::istreambuf_iterator<char>());
    std::string str2((std::istreambuf_iterator<char>(f2)), std::istreambuf_iterator<char>());
    return str1 == str2;
}

BOOST_AUTO_TEST_SUITE(minizip_tests)

BOOST_AUTO_TEST_CASE(zip_unzip_test)
{
    std::string err;
    const std::string dataDir("test/data/zip");
    const std::string zipFile("data.zip");
    const std::string readmeFile = strprintf("%s/README.md", dataDir);
    const std::string unzipDir = strprintf("%s/unzip", dataDir);
    const std::string unzipFile = strprintf("%s/%s/README.md", unzipDir, dataDir);

    /** invalid data dir */
    BOOST_CHECK_MESSAGE(!ZipCreate(zipFile, "not-exist-dir", err), err);

    /** create temporary data directory */
    BOOST_REQUIRE(boost::filesystem::create_directory(dataDir));

    /** create file with content */
    std::ofstream fReadme(readmeFile, std::ios_base::app);
    fReadme << "some content";
    fReadme.close();

    /** create zip */
    BOOST_REQUIRE_MESSAGE(ZipCreate(zipFile, dataDir, err), err);
    time_t time1 = boost::filesystem::last_write_time(zipFile);

    /** time1 resolution is seconds, so wait to get enough difference */
    MilliSleep(1000);

    /** overwrite zip */
    BOOST_REQUIRE_MESSAGE(ZipCreate(zipFile, dataDir, err), err);
    time_t time2 = boost::filesystem::last_write_time(zipFile);

    BOOST_CHECK(time2 > time1);

    /** create unzip directory */
    BOOST_REQUIRE(boost::filesystem::create_directory(unzipDir));

    /** extract */
    BOOST_REQUIRE_MESSAGE(ZipExtract(zipFile, unzipDir, err), err);
    BOOST_REQUIRE_MESSAGE(CompareFiles(readmeFile, unzipFile), "files are not equal");

    /** modify unzipped file */
    fReadme.open(unzipFile, std::ios_base::app);
    fReadme << " with modification";
    fReadme.close();
    BOOST_REQUIRE(!CompareFiles(readmeFile, unzipFile));

    /** extract overwrite */
    BOOST_REQUIRE_MESSAGE(ZipExtract(zipFile, unzipDir, err), err);
    BOOST_REQUIRE_MESSAGE(CompareFiles(readmeFile, unzipFile), "files are not equal");

    /** invalid input file */
    BOOST_CHECK_MESSAGE(!ZipExtract("not-exist-file", unzipDir, err), err);

    /** invalid output dir */
    BOOST_CHECK_MESSAGE(!ZipExtract(zipFile, "not-exist-dir", err), err);

    /** remove temporary files and directories */
    BOOST_REQUIRE(boost::filesystem::remove(zipFile));
    BOOST_REQUIRE(boost::filesystem::remove_all(dataDir));
}

BOOST_AUTO_TEST_SUITE_END()
