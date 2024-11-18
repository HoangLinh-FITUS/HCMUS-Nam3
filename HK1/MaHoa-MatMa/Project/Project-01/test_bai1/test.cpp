#include "pch.h"
#include "..\bai1\bai1.h"
#include <assert.h>
#include <string.h>

TEST(test_add, Test01) {
    EXPECT_EQ(add("2406", "FA1F"), "11E25");
}
TEST(test_add, Test02) {
    EXPECT_EQ(add("134AF412", "14A923"), "135F9D35");
}
TEST(test_add, Test03) {
    EXPECT_EQ(add("6C727BA19576BE9BFE7A", "121A41EB2F"), "6C727BA19588D8DDE9A9");
}
TEST(test_add, Test04) {
    EXPECT_EQ(add("F1C88", "F402133ACB9E6B1B5997"), "F402133ACB9E6B2A761F");
}
TEST(test_add, Test05) {
    EXPECT_EQ(add("E1", "1F"), "100");
}

TEST(test_subtract, Test01) {
    EXPECT_EQ(subtract("11E25", "FA1F"), "2406");
}
TEST(test_subtract, Test02) {
    EXPECT_EQ(subtract("135F9D35", "134AF412"), "14A923");
}
TEST(test_subtract, Test03) {
    EXPECT_EQ(subtract("6C727BA19588D8DDE9A9", "121A41EB2F"),"6C727BA19576BE9BFE7A");
}
TEST(test_subtract, Test04) {
    EXPECT_EQ(subtract("F402133ACB9E6B2A761F", "F402133ACB9E6B1B5997"),"F1C88");
}

TEST(test_div2, Test01) {
    EXPECT_EQ(div2("7C6C038214"), "3E3601C10A");
}

TEST(test_div2, Test02) {
    EXPECT_EQ(div2("FAB618514E"), "7D5B0C28A7");
}

TEST(test_div2, Test03) {
    EXPECT_EQ(div2("8E66813C26"), "4733409E13");
}
TEST(test_div2, Test04) {
    EXPECT_EQ(div2("D3A23A00730C9BF35F4B"), "69D11D0039864DF9AFA5");
}

TEST(test_multiple, Test01) {
    EXPECT_EQ(multiple("A3F", "5B7"), "3A8E09");
}

TEST(test_multiple, Test02) {
    EXPECT_EQ(multiple("13FABCD123", "FFBA5"), "13F54C7FDCD1C8F");
}
TEST(test_multiple, Test03) {
    EXPECT_EQ(multiple("7DC9911C1C289F264C14EAFBF62B301C9019022ED41C998121EA5D849766A6FF11CB64F6D2C3977B1DDC27DA5962F1A27C95547D0C1", "95A69A5E738CAB83A1A2D8E55A2F2C1C6A920ACB9E3477E5C15157E2A73A8147E5940900B35BF5B5C2BE9FB7FEA9FF9D59662626F85"), "49882E031EB2C2EC914972739877926C2E58C46584A72B7A1A7B782568932B200660E6233DC8758F40B5363C5900ACE41B02FB18458F5C11D9D17FFC69D81B3CE0B6A93E052D7D9A74C88EE94AFF37714D52F91C48FB0A1C8CF2D231BBCD896D422189C10D01113DB52345");
}
TEST(test_multiple, Test04) {
    EXPECT_EQ(multiple("132BFF576", "52D3F179"), "633F722ECF111AC6");
}
TEST(test_multiple, Test05) {
    EXPECT_EQ(multiple("3D2", "3A9949D94246077D7"), "DFDD9C1FFF2F889D35E");
}
TEST(test_multiple, Test06) {
    EXPECT_EQ(multiple("2A26701E9A0A0C38", "169"), "3B70341B27382B3AF8");
}

TEST(test_powerMod, Test01) {
     EXPECT_EQ(powerMod("12D87BD04E6CA4D0B", "DC6", "15A05CF3C28C8FC52"), "10F8ED5544006DDA1");
     
}
TEST(test_powerMod, Test02) {
    EXPECT_EQ(powerMod("373219EBF4D5BC492", "11A58", "21B8DF6B923076312"), "15F495CD4B2DA5BA0");
    
}
TEST(test_powerMod, Test03) {
    EXPECT_EQ(powerMod("998C59A88ECB6F52", "1463A", "33652019E13E7546A"), "292DC885079CBD352");
    
}
TEST(test_powerMod, Test04) {
    EXPECT_EQ(powerMod("46B6D1266AB3A6AA9", "4F17", "4382312A0701497BB"), "3FECECB4A2EE2CC45");

}

TEST(test_powerMod, Test05) {
    EXPECT_EQ(powerMod("18CBEF4BBEAEC4370", "8F82", "3470"), "1B60");
}


TEST(test_miller_bin, Test01) {
    EXPECT_EQ(miller_rabin("65"), 1);
}
TEST(test_miller_bin, Test02) {
    EXPECT_EQ(miller_rabin("2406"), 0);
}
TEST(test_miller_bin, Test03) {
    EXPECT_EQ(miller_rabin("2F60DFE"), 0);
}
TEST(test_miller_bin, Test04) {
    EXPECT_EQ(miller_rabin("A88B829A6205847EA7613"), 1);
}
TEST(test_miller_bin, Test05) {
    EXPECT_EQ(miller_rabin("28143B65205A51F7DCF2326F3BE9365E304A0CFBB0000B4D"), 0);
}

TEST(test_miller_bin, Test06) {
    EXPECT_EQ(miller_rabin("19986CAA6E3BE2696FE69EA63485397BC2903F427AE018CBC68E47C42914A57605170E90A3F20FC59CE84029"), 1);
}
TEST(test_miller_bin, Test07) {
    EXPECT_EQ(miller_rabin("5760B4038F5EB5B4784CC3CA1DAD02896BAD2E77E0F2817B6DF20BCEFF52681F34B3143333BD897ABB537DC76DA945D19DDEA25767D566274A3902AE97A701977A8E6C3A9F064361BD238E09807DE18BC285E6A0D75DB74A941047CEA3B4FE65EC77C1FCA71F3323017776D45FD989F5CA999FCC415DCD862646B5E6E1E8E05FD"), 1);

}
