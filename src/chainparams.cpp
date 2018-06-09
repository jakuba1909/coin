// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
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

//
// Main network
//
class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x3d;
        pchMessageStart[1] = 0x19;
        pchMessageStart[2] = 0xd1;
        pchMessageStart[3] = 0x09;

        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 1909;
        nRPCPort = 1919;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "Is Trump Racist? Is There a Double Standard? California Pastors Debate.";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        // vout[0].nValue = 0;
        vout[0].SetEmpty();
        CTransaction txNew(1, 1528281163, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1528281163; // 06/06/2018 @ 10:32am (UTC)
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 0;

        /** Genesis Block MainNet */
        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == 0xc08b7e10f87514a98554968c06868edbdb6d97ad560112b3c1f9c90c09656d95
        block.nTime = 1528281163
        block.nNonce = 0
        block.GetHash = 00001f66cb3ba8f5776cb750d621cb3390200580cc39f076b3f61efcf191fba0
        */
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0d37696317e9744d504eebb0acf83488bfc1dae4680bd47c45ea99c29ffdaa74"));
        assert(genesis.hashMerkleRoot == uint256("0xcf5e323171e20bf4e5759d8976886e00d5ca0d5aa74a6199c3dcbb53b154b5ae"));

        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("45.63.97.158", "45.63.97.158"));
        vSeeds.push_back(CDNSSeedData("46.101.255.105", "46.101.255.105"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,125);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,138);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "Mgn67cAEbNSs6Ajfq52HzNMbdtsxV9XHxL";
        nEndPoWBlock = 75000;
        nStartPoSBlock = 0;

        nStakeMinAge = 8 * 60 * 60; // 8 hours
        nStakeMaxAge = 15 * 24 * 60 * 60; // 15 days
        nStakeMaxAgeV2 =  30 * 24 * 60 * 60; // 30 days
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x2c;
        pchMessageStart[1] = 0xab;
        pchMessageStart[2] = 0x21;
        pchMessageStart[3] = 0xc3;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 8711;
        nRPCPort = 8102;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime    = 1528281163;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;

        /** Genesis Block TestNet */
        /*
        Hashed TestNet Genesis Block Output
//        block.hashMerkleRoot == 0x0d37696317e9744d504eebb0acf83488bfc1dae4680bd47c45ea99c29ffdaa74
        block.nTime = 1528281163
        block.nNonce = 0
        */
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0d37696317e9744d504eebb0acf83488bfc1dae4680bd47c45ea99c29ffdaa74"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,44);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,109);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        nEndPoWBlock = 0x7fffffff;
        nStakeMinAge = 20 * 60; // 20 mins
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x42;
        pchMessageStart[1] = 0xa4;
        pchMessageStart[2] = 0xc5;
        pchMessageStart[3] = 0x2b;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1528281163;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 10300;
        strDataDir = "regtest";

        /** Genesis Block TestNet */
        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == 0xc08b7e10f87514a98554968c06868edbdb6d97ad560112b3c1f9c90c09656d95
        block.nTime = 1493596890
        block.nNonce = 0
        block.GetHash = b772ef430a34e04f015ab7a4e4fbe2e882794a83b1dc0056573d74880649d073
        */
        // assert(hashGenesisBlock == hashRegNetGenesisBlock);

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}

unsigned int CChainParams::StakeMaxAge() const
{
    if (nBestHeight >= SOFT_FORK_VERSION_200)
        return nStakeMaxAgeV2;
    else
        return nStakeMaxAge;
}
