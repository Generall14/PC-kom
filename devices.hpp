typedef Factory f;

#define IMPL_EMPTY f::frameTransparent, f::mediumUIRS, f::mendiumRS, f::logicUiEmpty, f::frameBuilderEmpty, f::logUITerm, f::logFileDefault, f::logFormaterHtml
#define DESC_EMPTY "Implementacja pusta, bez kontroli jakichkolwiek protokołów.", "PC-KOM-EMPTY"
#define FAKE_EMPTY f::mendiumEmpty

#define IMPL_SG_1 f::frameSG1, f::mediumUIRS, f::mendiumRS, f::logicUiSG1, f::frameBuilderSG1, f::logUITerm, f::logFileDefault, f::logFormaterHtml
#define DESC_SG_1 "Implementacja dla prób i debugowania SG-1.", "SG-1: PC-Tester"
#define FAKE_SG_1 f::mendiumFakeGS1

#define IMPL_STAWROV f::frameStawrov, f::mediumUIRS, f::mendiumRS, f::logicUIStawrov, f::frameBuilderStawrov, f::logUITerm, f::logFileDefault, f::logFormaterHtml
#define DESC_STAWROV "Implementacja dla srednio zdefiniowanego wynalazku dla Stawrova.", "Grzegorzowy komunikator"
#define FAKE_STAWROV f::mendiumFakeStawrow

#define IMPL_ZR_3 f::frameZR3, f::mediumUIRS, f::mendiumRS, f::logicUIZR3, f::frameBuilderZR3, f::logUITerm, f::logFileDefault, f::logFormaterHtml
#define DESC_ZR_3 "Implementacja dla próbnego protokołu UMP Skolopendra i ZR-3.", "ZR-3: PC-tester"
#define FAKE_ZR_3 f::mendiumFakeZR3
