// Copyright (c) 2009-2009 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2018 The Galilel developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "clientversion.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>


struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000158fb5dd105270c131528150be31b7194f2c864d3041a0896826990bb6d"))
    (1, uint256("0x000006706b2455f852db5fc3c95eae68b5703d224b19f3b843efcbed4469e56b"))
    (2, uint256("0x00000c8968395a67b940b88333c9eceebdcdd6671c3e6658d11daadb4522905a"))
    (3, uint256("0x000001bdf3d3aad040b8c4dd58d7b6779cb4060d85de85ab2495f9b42c821134"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1519963807, // * UNIX timestamp of last checkpoint block
    295000,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1454124731,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x00;
        pchMessageStart[1] = 0x22;
        pchMessageStart[2] = 0x00;
        pchMessageStart[3] = 0xaa;
        vAlertPubKey = ParseHex("038b1d2e9faafacd8dfb20fa8f1ae9943def3b334808ebd0790d69a50d70d5f236");
        nDefaultPort = 8007;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // VIP starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = INT_MAX - 1; // 75%
        nRejectBlockOutdatedMajority = INT_MAX - 1; // 95%
        nToCheckBlockUpgradeMajority = INT_MAX - 1; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // VIP: 1 day
        nTargetSpacing = 1 * 60;  // VIP: 1 minute
        nMaturity = 60;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = (INT_MAX - 1) * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 15000;
        nModifierUpdateBlock = 1;
        nZerocoinStartTime = INT_MAX - 1;		/* Disabled */
        nBlockFirstGoodChecksum = INT_MAX - 1;	/* Disabled */
        nBlockFirstMint = INT_MAX - 1;			/* Disabled */
        nBlockEnforceSerialRange = INT_MAX - 1;	/* Disabled */
        nBlockZerocoinV2 = INT_MAX - 1;			/* Disabled */
        nEnforceNewSporkKey = 1580428800;		/* 01/31/2020 @ 12:00am (UTC): sporks signed after must use the new spork key */
        nRejectOldSporkKey = 1581033600;		/* 02/07/2020 @ 12:00am (UTC): after that reject old spork key */

        // Public coin spend enforcement
        nPublicZCSpends = INT_MAX - 1;			/* Disabled */

        const char* pszTimestamp = "TittieCoin Official Release";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0421fb0665876637d9d79d03a24f383393838fb9e3340858a6d5a70b079f4af57cfff3ca00310be5300d532adf6261ba98ac70d24d943a6be333bec6d7a6d93013") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1534082000;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2529900;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000158fb5dd105270c131528150be31b7194f2c864d3041a0896826990bb6d"));
        assert(genesis.hashMerkleRoot == uint256("0xc9dbe71f80b1de0feaca6072fad3e107010c084e413e4aedee1145b34aad6f93"));

        vSeeds.push_back(CDNSSeedData("seed1.limitlessvip.co.za", "seed1.limitlessvip.co.za")); // 1st DNS Seeder
        vSeeds.push_back(CDNSSeedData("seed2.limitlessvip.co.za", "seed2.limitlessvip.co.za")); // 2nd DNS Seeder
        vSeeds.push_back(CDNSSeedData("seed3.limitlessvip.co.za", "seed3.limitlessvip.co.za")); // 3rd DNS Seeder
        vSeeds.push_back(CDNSSeedData("seed4.limitlessvip.co.za", "seed4.limitlessvip.co.za")); // 4th DNS Seeder
        vSeeds.push_back(CDNSSeedData("seed5.limitlessvip.co.za", "seed5.limitlessvip.co.za")); // 5th DNS Seeder

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 127);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x13)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04e04d2785ad7104c15353185e25ed7f708982dd75a7cef8a3815a38dde00ad6040b2ef94018fccc9ebb18b7758a6c94721695321bf98526e641f49bea8c03e3cb";
        strSporkKeyOld = "038b1d2e9faafacd8dfb20fa8f1ae9943def3b334808ebd0790d69a50d70d5f236";
        strObfuscationPoolDummyAddress = "TWSbBnzmNkjDVaYHX7vkL1MqD96pRYWtZo";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT
        nRequiredMasternodeCollateral = 4000000 * COIN; // Masternode collateral amount

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMaxZerocoinPublicSpendsPerTransaction = 500; // Assume about 220 bytes each input
        nMinZerocoinMintFee = 1 * CENT; // high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; // the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; // full security level for accumulators
        nZerocoinHeaderVersion = 4; // block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 240; //The required confirmations for a zvip to be stakable

        nBudgetFeeConfirmations = 6; // number of confirmations for the finalization fee

        nBudgetSuperBlocks = 43200; // amount of blocks in a months period of time using 1 minutes per block
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget

        // VIP features
        strBootstrapUrl = "https://bootstrap.limitlessvip.co.za/v3/mainnet.zip";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
        nDefaultPort = 6804;
        nEnforceBlockUpgradeMajority = INT_MAX - 1; // 75%
        nRejectBlockOutdatedMajority = INT_MAX - 1; // 95%
        nToCheckBlockUpgradeMajority = INT_MAX - 1; // 4 days
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // VIP: 1 day
        nTargetSpacing = 1 * 60;  // VIP: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = (INT_MAX - 1) * COIN;
        nZerocoinStartTime = INT_MAX - 1;		/* Disabled */
        nBlockFirstGoodChecksum = INT_MAX - 1;	/* Disabled */
        nBlockFirstMint = INT_MAX - 1;			/* Disabled */
        nBlockEnforceSerialRange = INT_MAX - 1;	/* Disabled */
        nBlockZerocoinV2 = INT_MAX - 1;			/* Disabled */
        nEnforceNewSporkKey = 1579824000;		/* 01/24/2020 @ 12:00am (UTC): sporks signed after must use the new spork key */
        nRejectOldSporkKey = 1580428800;		/* 01/31/2020 @ 12:00am (UTC): after that reject old spork key */

        // Public coin spend enforcement
        nPublicZCSpends = INT_MAX - 1;			/* Disabled */

        /* Testnet genesis block. */
        genesis.nTime = 1454124731;
        genesis.nNonce = 2433720;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001e6ff9af6fade9c6e1f8117cb45993f56df681b3363f6e422885383cb7f"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("seed1.testnet.limitlessvip.co.za", "seed1.testnet.limitlessvip.co.za")); // 1st DNS Seeder 
        vSeeds.push_back(CDNSSeedData("seed2.testnet.limitlessvip.co.za", "seed2.testnet.limitlessvip.co.za")); // 2nd DNS Seeder 
        vSeeds.push_back(CDNSSeedData("seed3.testnet.limitlessvip.co.za", "seed3.testnet.limitlessvip.co.za")); // 3rd DNS Seeder 
        vSeeds.push_back(CDNSSeedData("seed4.testnet.limitlessvip.co.za", "seed4.testnet.limitlessvip.co.za")); // 4th DNS Seeder 
        vSeeds.push_back(CDNSSeedData("seed5.testnet.limitlessvip.co.za", "seed5.testnet.limitlessvip.co.za")); // 5th DNS Seeder 

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet limitless addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet limitless script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet Limitless BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet Limitless BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet Limitless BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "040eb1d2d6d56ed349b98e66b28af7d1a7eabe01be481d519adf631462ac553cfe02b6f05d7e005b98790b421d6a6af77f37cebf4ea8a1ccdc682ece4a313408cb";
        strSporkKeyOld = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; // Fri Oct 26 21:00:00 UTC 2018
        nRequiredMasternodeCollateral = 4000000 * COIN; // Masternode collateral amount
        nBudgetFeeConfirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nBudgetSuperBlocks = 120; // amount of blocks in a 2 hours period of time using 1 minutes per block
        nProposalEstablishmentTime = 60 * 5; // Proposals must be at least 5 mns old to make it into a test budget

        // VIP features
        strBootstrapUrl = "https://bootstrap.limitlessvip.co.za/v3/testnet.zip";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = INT_MAX - 1;
        nRejectBlockOutdatedMajority = INT_MAX - 1;
        nToCheckBlockUpgradeMajority = INT_MAX - 1;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // VIP: 1 day
        nTargetSpacing = 1 * 60;        // VIP: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nLastPOWBlock = 250;
        nMaturity = 60;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = (INT_MAX - 1) * COIN;
        nBlockZerocoinV2 = INT_MAX - 1;			/* Disabled */
        nZerocoinStartTime = INT_MAX - 1;		/* Disabled */
        nBlockEnforceSerialRange = INT_MAX - 1;	/* Disabled */

        // Public coin spend enforcement
        nPublicZCSpends = INT_MAX - 1;			/* Disabled */

        // Modify the regtest genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1454124731;
        genesis.nNonce = 2433720;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;
        assert(hashGenesisBlock == uint256("0x000001e6ff9af6fade9c6e1f8117cb45993f56df681b3363f6e422885383cb7f"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

bool ParamsSelected()
{
    return pCurrentParams != nullptr;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

uint64_t GetBlockChainSize()
{
    const uint64_t GB_BYTES = 1000000000LL;
    return 1LL * GB_BYTES;
}

bool VerifyGenesisBlock(const std::string& datadir, const uint256& genesisHash, std::string& err)
{
    const std::string path = strprintf("%s/blocks/blk00000.dat", datadir);
    FILE *fptr = fopen(path.c_str(), "rb");
    if (!fptr) {
        err = strprintf("Failed to open file: %s", path);
        return false;
    }

    CAutoFile filein(fptr, SER_DISK, CLIENT_VERSION);
    if (filein.IsNull()) {
        err = strprintf("Open block file failed: %s", path);
        return false;
    }

    char buf[MESSAGE_START_SIZE] = {0};
    filein.read(buf, MESSAGE_START_SIZE);
    if (memcmp(buf, Params().MessageStart(), MESSAGE_START_SIZE)) {
        err = strprintf("Invalid magic numer %s in the file: %s", HexStr(buf, buf + MESSAGE_START_SIZE), path);
        return false;
    }

    unsigned int nSize = 0;
    filein >> nSize;
    if (nSize < 80 || nSize > 2000000) {
        err = strprintf("Invalid block size %u in the file: %s", nSize, path);
        return false;
    }

    CBlock block;
    try {

        /** Read block */
        filein >> block;
    } catch (std::exception& e) {
        err = strprintf("Deserialize or I/O error: %s", e.what());
        return false;
    }

    /** Check block hash */
    if (block.GetHash() != genesisHash) {
        err = strprintf("Block hash %s does not match genesis block hash %s", block.GetHash().ToString(), genesisHash.ToString());
        return false;
    } else {
        return true;
    }
}
