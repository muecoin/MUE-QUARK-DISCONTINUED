// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>
#include <cstdio>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

static const unsigned int timeMainGenesisBlock = 1404668200;
uint256 hashMainGenesisBlock("0x0000070e6b650e7a6f20e015031b74c1f7e2b25ed4e419d8825ab9cc7eccfa92");
static uint256 bnMainProofOfWorkLimit(~uint256(0) >> 20);

static const int64_t nGenesisBlockRewardCoin = 0 * COIN;
static const int64_t nBlockRewardStartCoin = 40 * COIN;
static const int64_t nBlockRewardMinimumCoin = 1 * COIN;

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
     boost::assign::map_list_of
     ( 0, uint256("0x0000070e6b650e7a6f20e015031b74c1f7e2b25ed4e419d8825ab9cc7eccfa92"))
     ( 1, uint256("0x000008a6e7c1c9547c5b2e7bc1e30f813cc9684428e11e8bbc2f0f270943f318"))
     ( 50000, uint256("0x00000010be6026f1f993dc2d51654ffeab948269cc067ea0bd3760c87ecfc7d0"))
     ( 100000, uint256("0x000000380d10bb4bb67ff8ef4c193f9a83a9d390389138c8a690722fb1ee2094"))
     ( 150000, uint256("0x000000020ee690f42fb7937038de393a734c7b0094b0185491c8483038b54a79"))
     ( 200000, uint256("0x0000000089e209620a4819d46a7bdbba03924d3af1ae6f7668d8cc977d4e542c"))
     ( 250000, uint256("0x000000010f69e2769cdacd033779acf44c7dc1e862eb5314b7179088d1c38b1e"))
     ( 281000, uint256("0x00000000b1fb0f01e1eca91c8f6b869ec339f64210afeb793a5d75fc6c26b87b"))
     ( 460000, uint256("0x00000000add7d91ce6ee36330c6ac821da1bda24dfbdf534d56c74e7f87da395"))
     ( 470000, uint256("0x00000001a7e2ebc09c3e8df413180b800c0a61f26fe744e539ddd339f89a468f"))
     ( 490000, uint256("0x00000000dfba6baf869f8b5b43568b3008531046fef5a6caf83ca2082b264e21"))
     ( 500000, uint256("0x0000000041e7a379e70a0bd8e2fcb97e9badd40199df9d4232ede49c87706a88"))
     ( 510000, uint256("0x000000000249a0638e89196a806350de4c302687c8939486875dd26faf102838"))
     ( 520000, uint256("0x000000006f3915dd9fceb71a3bcd7db79f069a7a3f81f0292eb69422628bb7b5"))
     ( 530000, uint256("0x0000000028aa5e234f9923e3b600ed15faf597e9adea8c0a63cc407122fd5452"))
     ( 540000, uint256("0x0000000029695216538bc6f2ed706237a2a7fc120ab53f37a629d69735babde4"))
     ( 550000, uint256("0x00000000209dbf5cdabdee5c0d1c19ba9d531386cebe0958d0e8ddb83a6fc513"))
     ( 600000, uint256("0x000000000f10d6e637f485f504745d99b9b372ac55b68cdb1a91c9d8f69bfb08"))
     ( 650000, uint256("0x0000000026a04fea7e487f152114788eefd49cadbb9010897a26b43865183f93"))
     ( 700000, uint256("0x00000000260bb06e7ca785e93a09b515d88fb4a83afd4fdb7b4e900bb6905247"))
     ( 750000, uint256("0x00000000ce1b8f61a60a226f8012e4670e9349169062f91a3c4bc06c81ef2641"))
     ( 800000, uint256("0x00000000b6a1fe048f218cf5e7d9f82b55b116a824ff6b13b47a83212e9396dd"))
     ( 850000, uint256("0x00000000379bf14f72c598d749c0a006349287babb4c7207b0084840d3f62c4b"))
     ( 900000, uint256("0x000000007b8bbd5bcda8ec2060c9962392521aec0456268318b386b8cf0c9e87"))
     ( 950000, uint256("0x00000000e251898025e74013e802da3c3495fe1dafd45939201edd9800d40b43"))
     (1050000, uint256("0x000000004012b493615e64f2350ea80f565f123808620390410db57154e20d29"))
     (1100000, uint256("0x0000000002e262f10fbfb4a77267585cdd47c149df8a297f19334fa4cde5c557"))
     (1150000, uint256("0x00000000d2c8ff71189060a1d97f2672f4a38dcc0bd97826afdb6de39401804f"))
     (1200000, uint256("0x0000000011a0228ba4fbd7db486ec9c05dad9357cc93e6ffc2205870ef036dfd"))
     (1250000, uint256("0x00000000a162ace289fbdc4b117e3069efc760aca5d78e5c6acd6302aced9c96"))
     (1300000, uint256("0x0000000068e2a06a2457d47ed164ee22ca132cc7deaacb00a9c10b6b91ec3c9e"))
     ;
static const Checkpoints::CCheckpointData data = {
     &mapCheckpoints,
     1454721418, // * UNIX timestamp of last checkpoint block
     1588374,     // * total number of transactions between genesis and last checkpoint
                 //   (the tx=... number in the SetBestChain debug.log lines)
     2880.0      // * estimated number of transactions per day after checkpoint
 };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
     boost::assign::map_list_of
     ( 0, uint256("0x00000a3258cb9730d5c38f88885967b680be6eddc2d9fb1111cc6b5d2926ab72"))
     ;
static const Checkpoints::CCheckpointData dataTestnet = {
     &mapCheckpointsTestnet,
     1444779876,
     0,
     2880.0
 };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
     boost::assign::map_list_of
     ( 0, uint256("0x61147f8533435c8e0c895bdddabf1ffa88de3579478c21b62d134f727c4cdf17"))
     ;
static const Checkpoints::CCheckpointData dataRegtest = {
     &mapCheckpointsRegtest,
     0,
     0,
     0
 };

void CChainParams::MineNewGenesisBlock()
 {
     genesis.nTime=time(NULL);
     genesis.nNonce=0;
     uint256 thash;
     while(1)
     {
         thash=genesis.GetHash();
         if (this->CheckProofOfWork(thash, genesis.nBits))
             break;
         if ((genesis.nNonce & 0xFF) == 0)
         {
             printf("nonce %08X: hash = %s\n",genesis.nNonce, thash.ToString().c_str());
         }
         ++genesis.nNonce;
         if (genesis.nNonce == 0)
         {
             printf("NONCE WRAPPED, incrementing time\n");
             ++genesis.nTime;
         }
     }
     printf("genesis.nTime = %u;\n",genesis.nTime);
     printf("genesis.nNonce = %u;\n",genesis.nNonce);
     printf("assert(genesis.hashMerkleRoot == uint256(\"0x%s\"));\n",genesis.hashMerkleRoot.ToString().c_str());
     printf("//genesis hash: 0x%s\n", genesis.GetHash().ToString().c_str());
     printf("//genesis hash: 0x%s\n", genesis.GetHash().ToString().c_str());
     exit(1);
};

//need a different implementation here that doesn't use error() and that doesn't use Params() since it isn't yet usable
bool CChainParams::CheckProofOfWork(uint256 hash, unsigned int nBits)
{
   bool fNegative;
   bool fOverflow;
   uint256 bnTarget;

   bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

   // Check proof of work matches claimed amount
   if (hash > bnTarget)
       return false;

   return true;
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x04;
        pchMessageStart[1] = 0x05;
        pchMessageStart[2] = 0x05;
        pchMessageStart[3] = 0x04;
        vAlertPubKey = ParseHex("044160a269d0250990b4517566b47e24d2a94ba458edfe856d4a63c9c62cc3aa6354cddbc9371313af65616675fa009ab13aac2bb0f5ce6bf7b8e91861765144dc");
        nDefaultPort = 29948;
        bnProofOfWorkLimit = bnMainProofOfWorkLimit;
        //nSubsidyHalvingInterval = 840000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 10 * 40;
        nTargetSpacing = 40;
        nMaxTipAge = 24 * 60 * 60;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
         *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
         *   vMerkleTree: 4a5e1e
         */
        const char* pszTimestamp = "M O N E T A R Y U N I T";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = nGenesisBlockRewardCoin;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 112;
        genesis.nTime    = timeMainGenesisBlock + 5;
        genesis.nBits    = bnMainProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 139785;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == hashMainGenesisBlock);
        assert(genesis.hashMerkleRoot == uint256("0xa2cc3c1d8ab6e50e80464693199eefdd172d45c4129998394e636e47b5621364"));

        vSeeds.push_back(CDNSSeedData("dnsseed.exapool.com", "dnsseed.exapool.com"));
        vSeeds.push_back(CDNSSeedData("dnsseed.muewallet.com", "dnsseed.muewallet.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(15);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(9);
        base58Prefixes[SECRET_KEY] =     list_of(143);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x4d)(0x55)(0x45)(0x50);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x4d)(0x55)(0x45)(0x53);
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x8000001f);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
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
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x01;
        pchMessageStart[1] = 0x1A;
        pchMessageStart[2] = 0x39;
        pchMessageStart[3] = 0xF7;
        vAlertPubKey = ParseHex("04f98a3941171ec7de8b83593aa6f7459a7605fb055c3e82c330ef89e7a46b78efeaa1e15580dddf694cf668fcc57b3aa0a47555e33aa7b0cb86ef6393975dc8f4");
        nDefaultPort = 39948;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 400;
        nTargetSpacing = 40;
        nMaxTipAge = 0x7fffffff;

        genesis.nTime = 1444779876;
        genesis.nNonce = 4428938;
        assert(genesis.hashMerkleRoot == uint256("0xa2cc3c1d8ab6e50e80464693199eefdd172d45c4129998394e636e47b5621364"));

        //MineNewGenesisBlock();
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000a3258cb9730d5c38f88885967b680be6eddc2d9fb1111cc6b5d2926ab72"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(119);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(199);
        base58Prefixes[SECRET_KEY]     = list_of(247);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
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
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        //nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        nTargetSpacing = 2.5 * 60; // 2.5 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxTipAge = 24 * 60 * 60;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nTime = 1444777777;
        genesis.nNonce = 0;
        assert(genesis.hashMerkleRoot == uint256("0xa2cc3c1d8ab6e50e80464693199eefdd172d45c4129998394e636e47b5621364"));

        //MineNewGenesisBlock();
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x61147f8533435c8e0c895bdddabf1ffa88de3579478c21b62d134f727c4cdf17"));
        nDefaultPort = 39948;

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
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
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
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
    //virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
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

void SelectParams(CBaseChainParams::Network network) {
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
