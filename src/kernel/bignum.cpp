//
// Created by Patryk Szczypień on 09/11/2024.
//
#include <kernel/bignum.hpp>

const double BigNumber::TEN_CUBED = 1000.0;
const std::unordered_map<int, std::string> BigNumber::powTenToName = {
        {0, ""}, {3, "thousand"}, {6, "million"}, {9, "billion"}, {12, "trillion"},
        {15, "quadrillion"}, {18, "quintillion"}, {21, "sextillion"}, {24, "septillion"},
        {27, "octillion"}, {30, "nonillion"}, {33, "decillion"}, {36, "undecillion"},
        {39, "duodecillion"}, {42, "tredecillion"}, {45, "quattuordecillion"},
        {48, "quindecillion"}, {51, "sedecillion"}, {54, "septendecillion"},
        {57, "octodecillion"}, {60, "novendecillion"}, {63, "vigintillion"},
        {66, "unvigintillion"}, {69, "duovigintillion"}, {72, "tresvigintillion"},
        {75, "quattuorvigintillion"}, {78, "quinvigintillion"}, {81, "sesvigintillion"},
        {84, "septemvigintillion"}, {87, "octovigintillion"}, {90, "novemvigintillion"},
        {93, "trigintillion"}, {96, "untrigintillion"}, {99, "duotrigintillion"},
        {102, "trestrigintillion"}, {105, "quattuortrigintillion"}, {108, "quintrigintillion"},
        {111, "sestrigintillion"}, {114, "septentrigintillion"}, {117, "octotrigintillion"},
        {120, "noventrigintillion"}, {123, "quadragintillion"}, {126, "unquadragintillion"},
        {129, "duoquadragintillion"}, {132, "tresquadragintillion"}, {135, "quattuorquadragintillion"},
        {138, "quinquadragintillion"}, {141, "sesquadragintillion"}, {144, "septenquadragintillion"},
        {147, "octoquadragintillion"}, {150, "novenquadragintillion"}, {153, "quinquagintillion"},
        {156, "unquinquagintillion"}, {159, "duoquinquagintillion"}, {162, "tresquinquagintillion"},
        {165, "quattuorquinquagintillion"}, {168, "quinquinquagintillion"}, {171, "sesquinquagintillion"},
        {174, "septenquinquagintillion"}, {177, "octoquinquagintillion"}, {180, "novenquinquagintillion"},
        {183, "sexagintillion"}, {186, "unsexagintillion"}, {189, "duosexagintillion"},
        {192, "tresexagintillion"}, {195, "quattuorsexagintillion"}, {198, "quinsexagintillion"},
        {201, "sesexagintillion"}, {204, "septensexagintillion"}, {207, "octosexagintillion"},
        {210, "novensexagintillion"}, {213, "septuagintillion"}, {216, "unseptuagintillion"},
        {219, "duoseptuagintillion"}, {222, "treseptuagintillion"}, {225, "quattuorseptuagintillion"},
        {228, "quinseptuagintillion"}, {231, "seseptuagintillion"}, {234, "septenseptuagintillion"},
        {237, "octoseptuagintillion"}, {240, "novenseptuagintillion"}, {243, "octogintillion"},
        {246, "unoctogintillion"}, {249, "duooctogintillion"}, {252, "tresoctogintillion"},
        {255, "quattuoroctogintillion"}, {258, "quinoctogintillion"}, {261, "sexoctogintillion"},
        {264, "septemoctogintillion"}, {267, "octooctogintillion"}, {270, "novemoctogintillion"},
        {273, "nonagintillion"}, {276, "unnonagintillion"}, {279, "duononagintillion"},
        {282, "trenonagintillion"}, {285, "quattuornonagintillion"}, {288, "quinnonagintillion"},
        {291, "senonagintillion"}, {294, "septenonagintillion"}, {297, "octononagintillion"},
        {300, "novenonagintillion"}, {303, "centillion"}, {306, "uncentillion"},
        {309, "duocentillion"}, {312, "trescentillion"}, {315, "quattuorcentillion"},
        {318, "quincentillion"}, {321, "sexcentillion"}, {324, "septencentillion"},
        {327, "octocentillion"}, {330, "novencentillion"}, {333, "decicentillion"}
};

const std::unordered_map<int, std::string> BigNumber::powTenToAffix = {
        {0, ""}, {3, "K"}, {6, "M"}, {9, "B"}, {12, "T"},
        {15, "Qa"}, {18, "Qi"}, {21, "Sx"}, {24, "Sp"},
        {27, "Oc"}, {30, "N"}, {33, "Dc"}, {36, "UnDc"},
        {39, "DoDc"}, {42, "TrDc"}, {45, "QaDc"},
        {48, "QiDc"}, {51, "SxDc"}, {54, "SpDc"},
        {57, "OcDc"}, {60, "NoDc"}, {63, "Vg"},
        {66, "UnVg"}, {69, "DoVg"}, {72, "TrVg"},
        {75, "QaVg"}, {78, "QiVg"}, {81, "SxVg"},
        {84, "SpVg"}, {87, "OcVg"}, {90, "NoVg"},
        {93, "Tg"}, {96, "UnTg"}, {99, "DoTg"},
        {102, "TrTg"}, {105, "QaTg"}, {108, "QiTg"},
        {111, "SxTg"}, {114, "SpTg"}, {117, "OcTg"},
        {120, "NoTg"}, {123, "Qg"}, {126, "UnQg"},
        {129, "DoQg"}, {132, "TrQg"}, {135, "QaQg"},
        {138, "QiQg"}, {141, "SxQg"}, {144, "SpQg"},
        {147, "OcQg"}, {150, "NoQg"}, {153, "QgQ"},
        {156, "UnQq"}, {159, "DoQq"}, {162, "TrQq"},
        {165, "QaQq"}, {168, "QiQq"}, {171, "SxQq"},
        {174, "SpQq"}, {177, "OcQq"}, {180, "NoQq"},
        {183, "Sg"}, {186, "UnSg"}, {189, "DoSg"},
        {192, "TrSg"}, {195, "QaSg"}, {198, "QiSg"},
        {201, "SxSg"}, {204, "SpSg"}, {207, "OcSg"},
        {210, "NoSg"}, {213, "Spt"}, {216, "UnSpt"},
        {219, "DoSpt"}, {222, "TrSpt"}, {225, "QaSpt"},
        {228, "QiSpt"}, {231, "SxSpt"}, {234, "SpSpt"},
        {237, "OcSpt"}, {240, "NoSpt"}, {243, "Og"},
        {246, "UnOg"}, {249, "DoOg"}, {252, "TrOg"},
        {255, "QaOg"}, {258, "QiOg"}, {261, "SxOg"},
        {264, "SpOg"}, {267, "OcOg"}, {270, "NoOg"},
        {273, "Ng"}, {276, "UnNg"}, {279, "DoNg"},
        {282, "TrNg"}, {285, "QaNg"}, {288, "QiNg"},
        {291, "SxNg"}, {294, "SpNg"}, {297, "OcNg"},
        {300, "NoNg"}, {303, "Ct"}, {306, "UnCt"},
        {309, "DoCt"}, {312, "TrCt"}, {315, "QaCt"},
        {318, "QiCt"}, {321, "SxCt"}, {324, "SpCt"},
        {327, "OcCt"}, {330, "NoCt"}, {333, "DcCt"}
};
