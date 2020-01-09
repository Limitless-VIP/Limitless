// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2018 The Galilel developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//
// Unit tests for block-chain checkpoints
//

#include "checkpoints.h"

#include "uint256.h"
#include "test_limitless.h"

#include <boost/test/unit_test.hpp>


BOOST_FIXTURE_TEST_SUITE(Checkpoints_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p33934 = uint256("0xcf0c724c38db98886649d62c1f5d8f5aa2653cb2d4566cde84e7c80fa33ee2dd");
    uint256 p46310 = uint256("0x8162de462ce46707a0f933dec88ec37be6e1220cd4a662f24ab4ffc7c2bdb886");
    BOOST_CHECK(Checkpoints::CheckBlock(33934, p33934));
    BOOST_CHECK(Checkpoints::CheckBlock(46310, p46310));


    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckBlock(33934, p46310));
    BOOST_CHECK(!Checkpoints::CheckBlock(46310, p33934));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckBlock(33934+1, p46310));
    BOOST_CHECK(Checkpoints::CheckBlock(46310+1, p33934));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 46310);
}

BOOST_AUTO_TEST_SUITE_END()
