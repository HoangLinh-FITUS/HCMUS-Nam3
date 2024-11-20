#include "pch.h"
#include "..\bai1\bai1.h"
#include <assert.h>
#include <string.h>

TEST(test_add, Test01) {
    BigHex a = BigHex("2406");
    BigHex b = BigHex("FA1F");
    a += b;
    EXPECT_EQ(a, BigHex("11E25"));
}
TEST(test_add, Test02) {
    EXPECT_EQ(BigHex("134AF412") + BigHex("14A923"), BigHex("135F9D35"));
}
TEST(test_add, Test03) {
    EXPECT_EQ(BigHex("6C727BA19576BE9BFE7A") + BigHex("121A41EB2F"), BigHex("6C727BA19588D8DDE9A9"));
}
TEST(test_add, Test04) {
    EXPECT_EQ(BigHex("F1C88") + BigHex("F402133ACB9E6B1B5997"), BigHex("F402133ACB9E6B2A761F"));
}
TEST(test_add, Test05) {
    EXPECT_EQ(BigHex("E1") + BigHex("1F"), BigHex("100"));
}

TEST(test_subtract, Test01) {
    EXPECT_EQ(BigHex("11E25") - BigHex("FA1F"), BigHex("2406"));
}
TEST(test_subtract, Test02) {
    EXPECT_EQ(BigHex("135F9D35") - BigHex("134AF412"), BigHex("14A923"));
}
TEST(test_subtract, Test03) {
    EXPECT_EQ(BigHex("6C727BA19588D8DDE9A9") - BigHex("121A41EB2F"), BigHex("6C727BA19576BE9BFE7A"));
}
TEST(test_subtract, Test04) {
    EXPECT_EQ(BigHex("F402133ACB9E6B2A761F") - BigHex("F402133ACB9E6B1B5997"), BigHex("F1C88"));
}

TEST(test_div2, Test01) {
    EXPECT_EQ(BigHex("7C6C038214") / BigHex("2"), BigHex("3E3601C10A"));
}

TEST(test_div2, Test02) {
    EXPECT_EQ(BigHex("FAB618514E") / BigHex("2"), BigHex("7D5B0C28A7"));
}

TEST(test_div2, Test03) {
    EXPECT_EQ(BigHex("8E66813C26") / BigHex("2"), BigHex("4733409E13"));
}
TEST(test_div2, Test04) {
    EXPECT_EQ(BigHex("D3A23A00730C9BF35F4B") / BigHex("2"), BigHex("69D11D0039864DF9AFA5"));
}

TEST(test_multiple, Test01) {
    EXPECT_EQ(BigHex("A3F") * BigHex("5B7"), BigHex("3A8E09"));
}

TEST(test_multiple, Test02) {
    EXPECT_EQ(BigHex("13FABCD123") * BigHex("FFBA5"), BigHex("13F54C7FDCD1C8F"));
}
TEST(test_multiple, Test03) {
    EXPECT_EQ(BigHex("7DC9911C1C289F264C14EAFBF62B301C9019022ED41C998121EA5D849766A6FF11CB64F6D2C3977B1DDC27DA5962F1A27C95547D0C1") 
        * BigHex("95A69A5E738CAB83A1A2D8E55A2F2C1C6A920ACB9E3477E5C15157E2A73A8147E5940900B35BF5B5C2BE9FB7FEA9FF9D59662626F85"), 
        BigHex("49882E031EB2C2EC914972739877926C2E58C46584A72B7A1A7B782568932B200660E6233DC8758F40B5363C5900ACE41B02FB18458F5C11D9D17FFC69D81B3CE0B6A93E052D7D9A74C88EE94AFF37714D52F91C48FB0A1C8CF2D231BBCD896D422189C10D01113DB52345"));
}
TEST(test_multiple, Test04) {
    EXPECT_EQ(BigHex("132BFF576") * BigHex("52D3F179"), BigHex("633F722ECF111AC6"));
}
TEST(test_multiple, Test05) {
    EXPECT_EQ(BigHex("3D2") * BigHex("3A9949D94246077D7"), BigHex("DFDD9C1FFF2F889D35E"));
}
TEST(test_multiple, Test06) {
    EXPECT_EQ(BigHex("2A26701E9A0A0C38") * BigHex("169"), BigHex("3B70341B27382B3AF8"));
}

TEST(test_mod, Test01) {
    EXPECT_EQ(BigHex("4A") % BigHex("22"), BigHex("6"));
}

TEST(test_powerMod, Test01) {
    BigHex a("12D87BD04E6CA4D0B");

    EXPECT_EQ(a.power(BigHex("DC6"), BigHex("15A05CF3C28C8FC52")), BigHex("10F8ED5544006DDA1"));
}

TEST(test_powerMod, Test02) {
    EXPECT_EQ(BigHex("373219EBF4D5BC492").power(BigHex("11A58"), BigHex("21B8DF6B923076312")), BigHex("15F495CD4B2DA5BA0"));
    
}
TEST(test_powerMod, Test03) {
    EXPECT_EQ(BigHex("998C59A88ECB6F52").power(BigHex("1463A"), BigHex("33652019E13E7546A")), BigHex("292DC885079CBD352"));
    
}
TEST(test_powerMod, Test04) {
    EXPECT_EQ(BigHex("46B6D1266AB3A6AA9").power(BigHex("4F17"), BigHex("4382312A0701497BB")), BigHex("3FECECB4A2EE2CC45"));

}

TEST(test_powerMod, Test05) {
    EXPECT_EQ(BigHex("18CBEF4BBEAEC4370").power(BigHex("8F82"), BigHex("3470")), BigHex("1B60"));
}


TEST(test_miller_bin, Test01) {
    EXPECT_EQ(miller_rabin(BigHex("65")), 1);
}

TEST(test_miller_bin, Test02) {
    EXPECT_EQ(miller_rabin(BigHex("2406")), 0);
}
TEST(test_miller_bin, Test03) {
    EXPECT_EQ(miller_rabin(BigHex("2F60DFE")), 0);
}
TEST(test_miller_bin, Test04) {
    EXPECT_EQ(miller_rabin(BigHex("A88B829A6205847EA7613")), 1);
}
TEST(test_miller_bin, Test05) {
    EXPECT_EQ(miller_rabin(BigHex("28143B65205A51F7DCF2326F3BE9365E304A0CFBB0000B4D")), 0);
}

TEST(test_miller_bin, Test06) {
    EXPECT_EQ(miller_rabin(BigHex("19986CAA6E3BE2696FE69EA63485397BC2903F427AE018CBC68E47C42914A57605170E90A3F20FC59CE84029")), 1);
}
TEST(test_miller_bin, Test07) {
    EXPECT_EQ(miller_rabin(BigHex("5760B4038F5EB5B4784CC3CA1DAD02896BAD2E77E0F2817B6DF20BCEFF52681F34B3143333BD897ABB537DC76DA945D19DDEA25767D566274A3902AE97A701977A8E6C3A9F064361BD238E09807DE18BC285E6A0D75DB74A941047CEA3B4FE65EC77C1FCA71F3323017776D45FD989F5CA999FCC415DCD862646B5E6E1E8E05FD")), 1);
}

TEST(test_miller_bin, Test08) {
    EXPECT_EQ(miller_rabin(BigHex("151AB22BB48229ACA2790C29C926D7458ADE37F368C27117A8C2EE309B8F079B894509AF60EA0C1A27C9CFD6475CFA331B88E64180ECC1574DAF8AF9F64346A735A25369743A2BB9EAF3F783D8FB0E619FA84E2586DC22AD4FE17F650B3EFB06053968166EBB50D22945F6F949BB894CBCBB4540E33A96C2BEFCF9C9DCEBD96DDAAF")), 1);
}