// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "BatamPos, Tealcoin Mainnet is Now Launching!";
    const CScript genesisOutputScript = CScript() << ParseHex("04b8d9d52c276b2d4e260544d28954cb665261a19c8b212e2aded940c8cd308bf6ac5345374adc011481607616fe101a770bf41e8a9dd500399b7159a4020bfa70") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 12614000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 50;
        consensus.BIP34Hash = uint256S("05f546b32d94af6c1530abff3602eb88ed51cb6deb6d977afa85eddaef038380");
        consensus.powLimit = uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 4 * 60; // 4 minutes
        consensus.nPowTargetSpacing = 1 * 5; // 5 seconds
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nMinerConfirmationWindow = consensus.nPowTargetTimespan / consensus.nPowTargetSpacing; // Those parameters are for BIP 9 soft fork deployments
        consensus.nRuleChangeActivationThreshold = consensus.nMinerConfirmationWindow * 0.95; // Those parameters are for BIP 9 soft fork deployments
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1485561600; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1485561600; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000001cef900"); // block 118520

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x81;
        pchMessageStart[1] = 0xfa;
        pchMessageStart[2] = 0x32;
        pchMessageStart[3] = 0xde;
        nDefaultPort = 9993;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1523099414, 320, 0x2000ffff, 1, 5 * COIN);  // use "./nbits-to-difficulty.sh 0x2000ffff" to see the difficulty
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(genesis.hashMerkleRoot == uint256S("0xaa19eabcc7d37896fd16e9139b810bd2d13694ec7661aa51e45ef6310134ee5c"));
        assert(consensus.hashGenesisBlock == uint256S("0xaf41ff90c1af8bb30bd4e325fb2599caf4052512997adca28ac3d959233e8eea"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.push_back(CDNSSeedData("dnsseed-1.firstep-it.net", "dnsseed-1.firstep-it.net", false));
        vSeeds.push_back(CDNSSeedData("dnsseed-2.firstep-it.net", "dnsseed-2.firstep-it.net", false));
        vSeeds.push_back(CDNSSeedData("dnsseed-3.firstep-it.net", "dnsseed-3.firstep-it.net", false));
        vSeeds.push_back(CDNSSeedData("dnsseed-4.firstep-it.net", "dnsseed-4.firstep-it.net", false));
        vSeeds.push_back(CDNSSeedData("dnsseed-5.firstep-it.net", "dnsseed-5.firstep-it.net", false));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0x41); // prefix T
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,0x25); // prefix [F G]
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,0x25); // prefix [F G]
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,0x46); // prefix compressed=B, uncompressed=3 
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x31)(0xd3)(0xa6).convert_to_container<std::vector<unsigned char> >(); // prefix teaL
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x2a)(0x0b)(0x33).convert_to_container<std::vector<unsigned char> >(); // prefix TeaL

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

	checkpointData = (CCheckpointData) {
		boost::assign::map_list_of
			(     100, uint256S("0x7c0cc6c9711f693dd8ad1f358b76ac0bd2ae4e86d004d7fb3c65f584d003e0de")),
			(     230, uint256S("0x2cd25e3d3c24ddc579f0d5577a1b486890fe2336a5bddacb1e5c4caadd6d0c58")),
			(     280, uint256S("0xc1fc0e8a9c28fb1eac82b939da74c9513c72412f83be8a30b05186ae4d6d4897")),
			(     360, uint256S("0x45e0c1d0b633cbbbcae680e4c69b24da97d0d3b9981d1061524bfb368bd53141")),
			(     450, uint256S("0xc6563262a2c9a80f41596433d11c4919014efd9de1b1a97bee5b31ca0ec1da80")),
			(     500, uint256S("0x15127bfefee518701545dfb2e522c3a8f0319f06d96e9202883ccaa298f72d14")),
			(     800, uint256S("0xbcd884a4394aa546427143bf20409c988ab2951425c3bd6cb4320b7057ac6c7a")),
			(    1200, uint256S("0x11b1ab1c89bfe53aafd80768d50f5e98de5266198e9b2f139bf8e867e5aceca2")),
			(    1500, uint256S("0xa11dd912c0053f71718a35e24f558d2d47dd97d8bb5d3a5d8a90592615a74fe9")),
			(    2200, uint256S("0x73987167552f4237f7ab13e176598a3625f4e9a6f3191e9515ac8c3bf3e0b600")),
			(    6500, uint256S("0xe08b2cba2ae9551821c8d5f5b3db1b1aa83524fa71a2634f92a9d594a48289bb")),
			(    8000, uint256S("0xb71c7f42f08db06c6af3aca7dd4e0f02cf9828b8b36db3c8927e1e97b3e75098")),
			(   24000, uint256S("0x9d2442114143435ebb649c05b859feab726c551a82dd3262fdd6283ec4f3216f")),
			(   32000, uint256S("0xf85e2d3c1954f21a369d93fbee718a6273f7c5f397e32f57211f1072d9a9dd4d")),
			(   38000, uint256S("0xa8f9561fa20685041f703060804edb9a61ecd3a6da40a2477d07efdd89cfecea")),
			(   44000, uint256S("0xc9b59cad686de247e7bd5794a0d7b13dfc42c41356374f83282994e73d7e4370")),
			(   47000, uint256S("0x92d85b878ae50d5029a7a4fa76cefb4866be2de1e9303baaf8d648ef2291ec5a")),
			(   50000, uint256S("0x5687f698eb39b36291213a61981e9fb08b01618e51111c57d9f972d8a725ba80")),
			(   55000, uint256S("0xe7b4849407e92fa5e9981d0efdfd7fa6da109cdbdf98cdc11da33ddee152ed22")),
			(   58000, uint256S("0x9220ca01730f46b1391502e9506e22b17b0648c7ff249a3e2dbb966343dd3ed4")),
			(   76000, uint256S("0xcaa47e449a2e666e731b88c607b72ee93ffa6c218f5f63268707ee5313da1d9c")),
			(   80000, uint256S("0xe6ee8595817c9e9670aa557a67a4b0d99fd8cc5ebcba86cc6f32bd674cdea593")),
			(   90000, uint256S("0x3cd7b956487068dd85024c1dae92d14d191c481fe20dfffbd552c18f6d5fc499")),
			(  102000, uint256S("0xa7a3bd1defdf59d887c2ebcfc01d4865e9c33115e78224a8fa844faa404a658e")),
			(  118000, uint256S("0x5ce937df4432adb65171afe9469412255a0a4e32a003209ecc2b0e87226d7269")),
			1524082212, // * UNIX timestamp of last checkpoint block block 118500
			118500,   // * total number of transactions between genesis and last checkpoint
			0     // * estimated number of transactions per day after checkpoint
	};

    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 12614000;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 50;
        consensus.BIP34Hash = uint256S("46aac23877144deb7ff31c1bd96a2136a8f4aaa4c6e3b70280a170e01556ddfe");
        consensus.powLimit = uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 4 * 60; // 4 minutes
        consensus.nPowTargetSpacing = 1 * 5; // 5 seconds
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nMinerConfirmationWindow = consensus.nPowTargetTimespan / consensus.nPowTargetSpacing; // Those parameters are for BIP 9 soft fork deployments
        consensus.nRuleChangeActivationThreshold = consensus.nMinerConfirmationWindow * 0.75; // 7Those parameters are for BIP 9 soft fork deployments
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1483228800; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1517356801; // January 31st, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1483228800; // January 1, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000157d00"); //block 5500

        pchMessageStart[0] = 0x83;
        pchMessageStart[1] = 0xfc;
        pchMessageStart[2] = 0x34;
        pchMessageStart[3] = 0xf0;
        nDefaultPort = 19993;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1523099527, 37, 0x2000ffff, 1, 5 * COIN);  // use "./nbits-to-difficulty.sh 0x2000ffff" to see the difficulty
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(genesis.hashMerkleRoot == uint256S("0xaa19eabcc7d37896fd16e9139b810bd2d13694ec7661aa51e45ef6310134ee5c"));
        assert(consensus.hashGenesisBlock == uint256S("0xdc844a8692afe4d5106e3c330f1f761c12faa708f2483520535ae52fc7436d2e"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("dnsseed-1.firstep-it.net", "dnsseed-1.firstep-it.net", false));
        vSeeds.push_back(CDNSSeedData("dnsseed-2.firstep-it.net", "dnsseed-2.firstep-it.net", false));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0x7f); // prefix t
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,0x60); // prefix [f g]
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,0x60); // prefix [f g]
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,0xe6); // prefix compressed=b, uncompressed=8
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x31)(0xee)(0xbd).convert_to_container<std::vector<unsigned char> >(); // prefix tesT
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x2a)(0x26)(0x49).convert_to_container<std::vector<unsigned char> >(); // prefix TesT

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;


        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
			(    50, uint256S("0x46aac23877144deb7ff31c1bd96a2136a8f4aaa4c6e3b70280a170e01556ddfe")),
			(    80, uint256S("0xc1f3bcef4c1fb1c20465011ecf897b4c4c2012b91c4d0fd82a001c9e60609619")),
			(   200, uint256S("0x65cd9420d7fb1630bec43ef8e3717b2b3cb84ae381abe6a129d6e8a6c0ac59da")),
			(   220, uint256S("0xc04b8e0b9e5a7a6e37b5d43732a8a543876043a21a404b51008a971d39486e06")),
			(   320, uint256S("0x469884e70e31f29e2ca8c2f89abdea1c6afb809f669ea672136c762c29c68c55")),
			(   500, uint256S("0x1e13da77262c6af069d5ea588e27e1eb918bf44b77d5ba646151bb745d9dc3b5")),
			(  1500, uint256S("0x09353af6470ac1ac0ea940c0e773ec6cf9ccba43b6e98e2f5633fa9b67aa203d")),
			(  1900, uint256S("0xdd781d81449fd1f10e722a8d981a439ca6d18892f07329f769abe68a315d9e17")),
			(  1500, uint256S("0x09353af6470ac1ac0ea940c0e773ec6cf9ccba43b6e98e2f5633fa9b67aa203d")),
			(  4500, uint256S("0x15fc19b8c92b0e551929df10572f23da89d3f7ad7200b86efe4c48b1cd59316b")),
			(  5400, uint256S("0xb2e0533a277851553cbbd7dcad71cbf6a98402b8b76ca6d30629072835838b79")), 
            1523583587, // block 5450
            5450,
            0
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 12614000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 1000000000;
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 4 * 60; // 4 minutes
        consensus.nPowTargetSpacing = 1 * 5; // 5 seconds
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nMinerConfirmationWindow = consensus.nPowTargetTimespan / consensus.nPowTargetSpacing; // Those parameters are for BIP 9 soft fork deployments
        consensus.nRuleChangeActivationThreshold = consensus.nMinerConfirmationWindow * 0.75; // Those parameters are for BIP 9 soft fork deployments
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        pchMessageStart[0] = 0x85;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0x36;
        pchMessageStart[3] = 0xf2;
        nDefaultPort = 29993;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1523099637, 93, 0x2000ffff, 1, 5 * COIN);  // use "./nbits-to-difficulty.sh 0x2000ffff" to see the difficulty
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(genesis.hashMerkleRoot == uint256S("0xaa19eabcc7d37896fd16e9139b810bd2d13694ec7661aa51e45ef6310134ee5c"));
        assert(consensus.hashGenesisBlock == uint256S("0x5955c35ea732ddf7431786ae8f2b2413c9b0cadc5294d7a414e277cedafe65fb"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 
        fTestnetToBeDeprecatedFieldRPC = false;

	checkpointData = (CCheckpointData){
		boost::assign::map_list_of
			( 0, uint256S("0x5955c35ea732ddf7431786ae8f2b2413c9b0cadc5294d7a414e277cedafe65fb")),
			0,
			0,
			0
	};

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,0x7f); // prefix t
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,0x60); // prefix [f g]
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,0x60); // prefix [f g]
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,0xe6); // prefix compressed=b, uncompressed=8
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x31)(0xee)(0xbd).convert_to_container<std::vector<unsigned char> >(); // prefix tesT
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x2a)(0x26)(0x49).convert_to_container<std::vector<unsigned char> >(); // prefix TesT
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
 
