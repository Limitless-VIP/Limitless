// Copyright (c) 2009-2009 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2018 The Galilel developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("limitless:UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("limitless:UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("limitless:UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?label=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX"));
    QVERIFY(rv.label == QString("Some Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("limitless:UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("limitless:UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("limitless:UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?amount=100&label=Some Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));

    uri.setUrl(QString("limitless:UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("limitless://UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("limitless:UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("limitless:UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?amount=1,000&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("limitless:UUr5nDmykhun1HWM7mJAqLVeLzoGtx19dX?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}
