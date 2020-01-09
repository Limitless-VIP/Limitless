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

#ifndef LIMITLESS_ZIPUTIL_H
#define LIMITLESS_ZIPUTIL_H

#include <string>
#include <vector>

/**
 * Create zip archive, add input file/folder to the archive.
 * Folder recursively added to the archive. Overwrite existing archive.
 *
 * @param strOutputPath[in] path to the output zip file
 * @param strInputPath[in] path to the input file/folder
 * @param err[out] error description in case of fail
 * @return true - success, false - fail, see err for details
 */
bool ZipCreate(const std::string& strOutputPath, const std::string& strInputPath, std::string& err);

/**
 * Extract zip archive into specified folder.
 * Overwrite existing files in the output folder.
 *
 * @param strInputPath[in] path to the input zip file
 * @param strOutputPath[in] path to the output folder
 * @param err[out] error description in case of fail
 * @return true - success, false - fail, see err for details
 */
bool ZipExtract(const std::string& strInputPath, const std::string& strOutputPath, std::string& err);

#endif /** LIMITLESS_ZIPUTIL_H */
