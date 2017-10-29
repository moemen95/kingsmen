#include <bits/stdc++.h>
typedef unsigned long long ull;
using namespace std;

class Board {


public:

    unordered_map<ull, int> zobristTable;

    const double EPS = 1e-8;

    const int CASTLEKINGSIDE = 1;
    const int CASTLEQUEENSIDE = 2;
    const int ENPASSANT = 3;
    const int PROMOTEKNIGHT = 4;
    const int PROMOTEBISHOP = 5;
    const int PROMOTEROOK = 6;
    const int PROMOTEQUEEN = 7;

    static const int MAX_GAME_LENGTH = 1024;

    // Zobrist tables
    ull pawn[2][64] = {{0x79ad695501e7d1e8L, 0x8249a47aee0e41f7L, 0x637a7780decfc0d9L, 0x19fc8a768cf4b6d4L, 0x7bcbc38da25a7f3cL, 0x5093417aa8a7ed5eL, 0x7fb9f855a997142L,  0x5355f900c2a82dc7L,
                                              0xe99d662af4243939L, 0xa49cd132bfbf7cc4L, 0xce26c0b95c980d9L, 0xbb6e2924f03912eaL, 0x24c3c94df9c8d3f6L, 0xdabf2ac8201752fcL, 0xf145b6beccdea195L, 0x14acbaf4777d5776L,
                                              0xf9b89d3e99a075c2L, 0x70ac4cd9f04f21f5L, 0x9a85ac909a24eaa1L, 0xee954d3c7b411f47L, 0x72b12c32127fed2bL, 0x54b3f4fa5f40d873L, 0x8535f040b9744ff1L, 0x27e6ad7891165c3fL,
                                              0x8de8dca9f03cc54eL, 0xff07f64ef8ed14d0L, 0x92237ac237f3859L,  0x87bf02c6b49e2ae9L, 0x1920c04d47267bbdL, 0xae4a9346cc3f7cf2L, 0xa366e5b8c54f48b8L, 0x87b3e2b2b5c907b1L,
                                              0x6304d09a0b3738c4L, 0x4f80f7a035dafb04L, 0x9a74acb964e78cb3L, 0x1e1032911fa78984L, 0x5bfea5b4712768e9L, 0x390e5fb44d01144bL, 0xb3f22c3d0b0b38edL, 0x9c1633264db49c89L,
                                              0x7b32f7d1e03680ecL, 0xef927dbcf00c20f2L, 0xdfd395339cdbf4a7L, 0x6503080440750644L, 0x1881afc9a3a701d6L, 0x506aacf489889342L, 0x5b9b63eb9ceff80cL, 0x2171e64683023a08L,
                                              0xede6c87f8477609dL, 0x3c79a0ff5580ef7fL, 0xf538639ce705b824L, 0xcf464cec899a2f8aL, 0x4a750a09ce9573f7L, 0xb5889c6e15630a75L, 0x5a7e8a57db91b77L,  0xb9fd7620e7316243L,
                                              0x73a1921916591cbdL, 0x70eb093b15b290ccL, 0x920e449535dd359eL, 0x43fcae60cc0eba0L,  0xa246637cff328532L, 0x97d7374c60087b73L, 0x86536b8cf3428a8cL, 0x799e81f05bc93f31L},

                                      {0xe83a908ff2fb60caL, 0xfbbad1f61042279L,  0x3290ac3a203001bfL, 0x75834465489c0c89L, 0x9c15f73e62a76ae2L, 0x44db015024623547L, 0x2af7398005aaa5c7L, 0x9d39247e33776d41L,
                                              0x239f8b2d7ff719ccL, 0x5db4832046f3d9e5L, 0x11355146fd56395L, 0x40bdf15d4a672e32L, 0xd021ff5cd13a2ed5L, 0x9605d5f0e25ec3b0L, 0x1a083822ceafe02dL, 0xd7e765d58755c10L,
                                              0x4bb38de5e7219443L, 0x331478f3af51bbe6L, 0xf3218f1c9510786cL, 0x82c7709e781eb7ccL, 0x7d11cdb1c3b7adf0L, 0x7449bbff801fed0bL, 0x679f848f6e8fc971L, 0x5d1a1ae85b49aa1L,
                                              0x24aa6c514da27500L, 0xc9452ca81a09d85dL, 0x7b0500ac42047ac4L, 0xb4ab30f062b19abfL, 0x19f3c751d3e92ae1L, 0x87d2074b81d79217L, 0x8dbd98a352afd40bL, 0xaa649c6ebcfd50fcL,
                                              0x735e2b97a4c45a23L, 0x3575668334a1dd3bL, 0x9d1bc9a3dd90a94L,  0x637b2b34ff93c040L, 0x3488b95b0f1850fL,  0xa71b9b83461cbd93L, 0x14a68fd73c910841L, 0x4c9f34427501b447L,
                                              0xfcf7fe8a3430b241L, 0x5c82c505db9ab0faL, 0x51ebdc4ab9ba3035L, 0x9f74d14f7454a824L, 0xbf983fe0fe5d8244L, 0xd310a7c2ce9b6555L, 0x1fcbacd259bf02e7L, 0x18727070f1bd400bL,
                                              0x96d693460cc37e5dL, 0x4de0b0f40f32a7b8L, 0x6568fca92c76a243L, 0x11d505d4c351bd7fL, 0x7ef48f2b83024e20L, 0xb9bc6c87167c33e7L, 0x8c74c368081b3075L, 0x3253a729b9ba3ddeL,
                                              0xec16ca8aea98ad76L, 0x63dc359d8d231b78L, 0x93c5b5f47356388bL, 0x39f890f579f92f88L, 0x5f0f4a5898171bb6L, 0x42880b0236e4d951L, 0x6d2bdcdae2919661L, 0x42e240cb63689f2fL}};;
    ull rook[2][64] = {{0xd18d8549d140caeaL, 0x1cfc8bed0d681639L, 0xca1e3785a9e724e5L, 0xb67c1fa481680af8L, 0xdfea21ea9e7557e3L, 0xd6b6d0ecc617c699L, 0xfa7e393983325753L, 0xa09e8c8c35ab96deL,
                                              0x7983eed3740847d5L, 0x298af231c85bafabL, 0x2680b122baa28d97L, 0x734de8181f6ec39aL, 0x53898e4c3910da55L, 0x1761f93a44d5aefeL, 0xe4dbf0634473f5d2L, 0x4ed0fe7e9dc91335L,
                                              0x261e4e4c0a333a9dL, 0x219b97e26ffc81bdL, 0x66b4835d9eafea22L, 0x4cc317fb9cddd023L, 0x50b704cab602c329L, 0xedb454e7badc0805L, 0x9e17e49642a3e4c1L, 0x66c1a2a1a60cd889L,
                                              0x36f60e2ba4fa6800L, 0x38b6525c21a42b0eL, 0xf4f5d05c10cab243L, 0xcf3f4688801eb9aaL, 0x1ddc0325259b27deL, 0xb9571fa04dc089c8L, 0xd7504dfa8816edbbL, 0x1fe2cca76517db90L,
                                              0xe699ed85b0dfb40dL, 0xd4347f66ec8941c3L, 0xf4d14597e660f855L, 0x8b889d624d44885dL, 0x258e5a80c7204c4bL, 0xaf0c317d32adaa8aL, 0x9c4cd6257c5a3603L, 0xeb3593803173e0ceL,
                                              0xb090a7560a968e3L,  0x2cf9c8ca052f6e9fL, 0x116d0016cb948f09L, 0xa59e0bd101731a28L, 0x63767572ae3d6174L, 0xab4f6451cc1d45ecL, 0xc2a1e7b5b459aeb5L, 0x2472f6207c2d0484L,
                                              0x804456af10f5fb53L, 0xd74bbe77e6116ac7L, 0x7c0828dd624ec390L, 0x14a195640116f336L, 0x2eab8ca63ce802d7L, 0xc6e57a78fbd986e0L, 0x58efc10b06a2068dL, 0xabeeddb2dde06ff1L,
                                              0x12a8f216af9418c2L, 0xd4490ad526f14431L, 0xb49c3b3995091a36L, 0x5b45e522e4b1b4efL, 0xa1e9300cd8520548L, 0x49787fef17af9924L, 0x3219a39ee587a30L,  0xebe9ea2adf4321c7L},

                                      {0x10dcd78e3851a492L, 0xb438c2b67f98e5e9L, 0x43954b3252dc25e5L, 0xab9090168dd05f34L, 0xce68341f79893389L, 0x36833336d068f707L, 0xdcdd7d20903d0c25L, 0xda3a361b1c5157b1L,
                                              0xaf08da9177dda93dL, 0xac12fb171817eee7L, 0x1fff7ac80904bf45L, 0xa9119b60369ffebdL, 0xbfced1b0048eac50L, 0xb67b7896167b4c84L, 0x9b3cdb65f82ca382L, 0xdbc27ab5447822bfL,
                                              0x6dd856d94d259236L, 0x67378d8eccef96cbL, 0x9fc477de4ed681daL, 0xf3b8b6675a6507ffL, 0xc3a9dc228caac9e9L, 0xc37b45b3f8d6f2baL, 0xb559eb1d04e5e932L, 0x1b0cab936e65c744L,
                                              0x7440fb816508c4feL, 0x9d266d6a1cc0542cL, 0x4dda48153c94938aL, 0x74c04bf1790c0efeL, 0xe1925c71285279f5L, 0x8a8e849eb32781a5L, 0x73973751f12dd5eL,  0xa319ce15b0b4db31L,
                                              0x94ebc8abcfb56daeL, 0xd7a023a73260b45cL, 0x72c8834a5957b511L, 0x8f8419a348f296bfL, 0x1e152328f3318deaL, 0x4838d65f6ef6748fL, 0xd6bf7baee43cac40L, 0x13328503df48229fL,
                                              0xdd69a0d8ab3b546dL, 0x65ca5b96b7552210L, 0x2fd7e4b9e72cd38cL, 0x51d2b1ab2ddfb636L, 0x9d1d84fcce371425L, 0xa44cfe79ae538bbeL, 0xde68a2355b93cae6L, 0x9fc10d0f989993e0L,
                                              0x3a938fee32d29981L, 0x2c5e9deb57ef4743L, 0x1e99b96e70a9be8bL, 0x764dbeae7fa4f3a6L, 0xaac40a2703d9bea0L, 0x1a8c1e992b941148L, 0x73aa8a564fb7ac9eL, 0x604d51b25fbf70e2L,
                                              0x8fe88b57305e2ab6L, 0x89039d79d6fc5c5cL, 0x9bfb227ebdf4c5ceL, 0x7f7cc39420a3a545L, 0x3f6c6af859d80055L, 0xc8763c5b08d1908cL, 0x469356c504ec9f9dL, 0x26e6db8ffdf5adfeL}};

    ull knight[2][64] = {{0x3bba57b68871b59dL, 0xdf1d9f9d784ba010L, 0x94061b871e04df75L, 0x9315e5eb3a129aceL, 0x8bd35cc38336615L,  0xfe9a44e9362f05faL, 0x78e37644e7cad29eL, 0xc547f57e42a7444eL,
                                                0x4f2a5cb07f6a35b3L, 0xa2f61bb6e437fdb5L, 0xa74049dac312ac71L, 0x336f52f8ff4728e7L, 0xd95be88cd210ffa7L, 0xd7f4f2448c0ceb81L, 0xf7a255d83bc373f8L, 0xd2b7adeeded1f73fL,
                                                0x4c0563b89f495ac3L, 0x18fcf680573fa594L, 0xfcaf55c1bf8a4424L, 0x39b0bf7dde437ba2L, 0xf3a678cad9a2e38cL, 0x7ba2484c8a0fd54eL, 0x16b9f7e06c453a21L, 0x87d380bda5bf7859L,
                                                0x35cab62109dd038aL, 0x32095b6d4ab5f9b1L, 0x3810e399b6f65ba2L, 0x9d1d60e5076f5b6fL, 0x7a1ee967d27579e2L, 0x68ca39053261169fL, 0x8cffa9412eb642c1L, 0x40e087931a00930dL,
                                                0x9d1dfa2efc557f73L, 0x52ab92beb9613989L, 0x528f7c8602c5807bL, 0xd941aca44b20a45bL, 0x4361c0ca3f692f12L, 0x513e5e634c70e331L, 0x77a225a07cc2c6bdL, 0xa90b24499fcfafb1L,
                                                0x284c847b9d887aaeL, 0x56fd23c8f9715a4cL, 0xcd9a497658a5698L,  0x5a110c6058b920a0L, 0x4208fe9e8f7f2d6L,  0x7a249a57ec0c9ba2L, 0x1d1260a51107fe97L, 0x722ff175f572c348L,
                                                0x5e11e86d5873d484L, 0xed9b915c66ed37eL,  0xb0183db56ffc6a79L, 0x506e6744cd974924L, 0x881b82a13b51b9e2L, 0x9a9632e65904ad3cL, 0x742e1e651c60ba83L, 0x4feabfbbdb619cbL,
                                                0x48cbff086ddf285aL, 0x99e7afeabe000731L, 0x93c42566aef98ffbL, 0xa865a54edcc0f019L, 0xd151d86adb73615L,  0xdab9fe6525d89021L, 0x1b85d488d0f20cc5L, 0xf678647e3519ac6eL},

                                        {0xdd2c5bc84bc8d8fcL, 0xae623fd67468aa70L, 0xff6712ffcfd75ea1L, 0x930f80f4e8eb7462L, 0x45f20042f24f1768L, 0xbb215798d45df7afL, 0xefac4b70633b8f81L, 0x56436c9fe1a1aa8dL,
                                                0xaa969b5c691ccb7aL, 0x43539603d6c55602L, 0x1bede3a3aef53302L, 0xdec468145b7605f6L, 0x808bd68e6ac10365L, 0xc91800e98fb99929L, 0x22fe545401165f1cL, 0x7eed120d54cf2dd9L,
                                                0x28aed140be0bb7ddL, 0x10cff333e0ed804aL, 0x91b859e59ecb6350L, 0xb415938d7da94e3cL, 0x21f08570f420e565L, 0xded2d633cad004f6L, 0x65942c7b3c7e11aeL, 0xa87832d392efee56L,
                                                0xaef3af4a563dfe43L, 0x480412bab7f5be2aL, 0xaf2042f5cc5c2858L, 0xef2f054308f6a2bcL, 0x9bc5a38ef729abd4L, 0x2d255069f0b7dab3L, 0x5648f680f11a2741L, 0xc5cc1d89724fa456L,
                                                0x4dc4de189b671a1cL, 0x66f70b33fe09017L,  0x9da4243de836994fL, 0xbce5d2248682c115L, 0x11379625747d5af3L, 0xf4f076e65f2ce6f0L, 0x52593803dff1e840L, 0x19afe59ae451497fL,
                                                0xf793c46702e086a0L, 0x763c4a1371b368fdL, 0x2df16f761598aa4fL, 0x21a007933a522a20L, 0xb3819a42abe61c87L, 0xb46ee9c5e64a6e7cL, 0xc07a3f80c31fb4b4L, 0x51039ab7712457c3L,
                                                0x9ae182c8bc9474e8L, 0xb05ca3f564268d99L, 0xcfc447f1e53c8e1bL, 0x4850e73e03eb6064L, 0x2c604a7a177326b3L, 0xbf692b38d079f23L,  0xde336a2a4bc1c44bL, 0xd7288e012aeb8d31L,
                                                0x6703df9d2924e97eL, 0x8ec97d2917456ed0L, 0x9c684cb6c4d24417L, 0xfc6a82d64b8655fbL, 0xf9b5b7c4acc67c96L, 0x69b97db1a4c03dfeL, 0xe755178d58fc4e76L, 0xa4fc4bd4fc5558caL}};

    ull bishop[2][64] = {{0x2fe4b17170e59750L, 0xe8d9ecbe2cf3d73fL, 0xb57d2e985e1419c7L, 0x572b974f03ce0bbL, 0xa8d7e4dab780a08dL, 0x4715ed43e8a45c0aL, 0xc330de426430f69dL, 0x23b70edb1955c4bfL,
                                                0x49353fea39ba63b1L, 0xf85b2b4fbcde44b7L, 0xbe7444e39328a0acL, 0x3e2b8bcbf016d66dL, 0x964e915cd5e2b207L, 0x1725cabfcb045b00L, 0x7fbf21ec8a1f45ecL, 0x11317ba87905e790L,
                                                0xe94c39a54a98307fL, 0xaa70b5b4f89695a2L, 0x3bdbb92c43b17f26L, 0xcccb7005c6b9c28dL, 0x18a6a990c8b35ebdL, 0xfc7c95d827357afaL, 0x1fca8a92fd719f85L, 0x1dd01aafcd53486aL,
                                                0xdbc0d2b6ab90a559L, 0x94628d38d0c20584L, 0x64972d68dee33360L, 0xb9c11d5b1e43a07eL, 0x2de0966daf2f8b1cL, 0x2e18bc1ad9704a68L, 0xd4dba84729af48adL, 0xb7a0b174cff6f36eL,
                                                0xcffe1939438e9b24L, 0x79999cdff70902cbL, 0x8547eddfb81ccb94L, 0x7b77497b32503b12L, 0x97fcaacbf030bc24L, 0x6ced1983376fa72bL, 0x7e75d99d94a70f4dL, 0xd2733c4335c6a72fL,
                                                0x9ff38fed72e9052fL, 0x9f65789a6509a440L, 0x981dcd296a8736dL,  0x5873888850659ae7L, 0xc678b6d860284a1cL, 0x63e22c147b9c3403L, 0x92fae24291f2b3f1L, 0x829626e3892d95d7L,
                                                0x7a76956c3eafb413L, 0x7f5126dbba5e0ca7L, 0x12153635b2c0cf57L, 0x7b3f0195fc6f290fL, 0x5544f7d774b14aefL, 0x56c074a581ea17feL, 0xe7f28ecd2d49eecdL, 0xe479ee5b9930578cL,
                                                0x7f9d1a2e1ebe1327L, 0x5d0a12f27ad310d1L, 0x3bc36e078f7515d7L, 0x4da8979a0041e8a9L, 0x950113646d1d6e03L, 0x7b4a38e32537df62L, 0x8a1b083821f40cb4L, 0x3d5774a11d31ab39L},

                                        {0x501f65edb3034d07L, 0x907f30421d78c5deL, 0x1a804aadb9cfa741L, 0xce2a38c344a6eedL, 0xd363eff5f0977996L, 0x2cd16e2abd791e33L, 0x58627e1a149bba21L, 0x7f9b6af1ebf78bafL,
                                                0x364f6ffa464ee52eL, 0x6c3b8e3e336139d3L, 0xf943aee7febf21b8L, 0x88e049589c432e0L,  0xd49503536abca345L, 0x3a6c27934e31188aL, 0x957baf61700cff4eL, 0x37624ae5a48fa6e9L,
                                                0xb344c470397bba52L, 0xbac7a9a18531294bL, 0xecb53939887e8175L, 0x565601c0364e3228L, 0xef1955914b609f93L, 0x16f50edf91e513afL, 0x56963b0dca418fc0L, 0xd60f6dcedc314222L,
                                                0x99170a5dc3115544L, 0x59b97885e2f2ea28L, 0xbc4097b116c524d2L, 0x7a13f18bbedc4ff5L, 0x71582401c38434dL,  0xb422061193d6f6a7L, 0xb4b81b3fa97511e2L, 0x65d34954daf3cebdL,
                                                0xc7d9f16864a76e94L, 0x7bd94e1d8e17debcL, 0xd873db391292ed4fL, 0x30f5611484119414L, 0x565c31f7de89ea27L, 0xd0e4366228b03343L, 0x325928ee6e6f8794L, 0x6f423357e7c6a9f9L,
                                                0x35dd37d5871448afL, 0xb03031a8b4516e84L, 0xb3f256d8aca0b0b9L, 0xfd22063edc29fcaL,  0xd9a11fbb3d9808e4L, 0x3a9bf55ba91f81caL, 0xc8c93882f9475f5fL, 0x947ae053ee56e63cL,
                                                0xbbe83f4ecc2bdecbL, 0xcd454f8f19c5126aL, 0xc62c58f97dd949bfL, 0x693501d628297551L, 0xb9ab4ce57f2d34f3L, 0x9255abb50d532280L, 0xebfafa33d7254b59L, 0xe9f6082b05542e4eL,
                                                0x98954d51fff6580L,  0x8107fccf064fcf56L, 0x852f54934da55cc9L, 0x9c7e552bc76492fL,  0xe9f6760e32cd8021L, 0xa3bc941d0a5061cbL, 0xba89142e007503b8L, 0xdc842b7e2819e230L}};

    ull queen[2][64] = {{0x720bf5f26f4d2eaaL, 0x1c2559e30f0946beL, 0xe328e230e3e2b3fbL, 0x87e79e5a57d1d13L,  0x8dd9bdfd96b9f63L,  0x64d0e29eea8838b3L, 0xddf957bc36d8b9caL, 0x6ffe73e81b637fb3L,
                                               0x93b633abfa3469f8L, 0xe846963877671a17L, 0x59ac2c7873f910a3L, 0x660d3257380841eeL, 0xd813f2fab7f5c5caL, 0x4112cf68649a260eL, 0x443f64ec5a371195L, 0xb0774d261cc609dbL,
                                               0xb5635c95ff7296e2L, 0xed2df21216235097L, 0x4a29c6465a314cd1L, 0xd83cc2687a19255fL, 0x506c11b9d90e8b1dL, 0x57277707199b8175L, 0xcaf21ecd4377b28cL, 0xc0c0f5a60ef4cdcfL,
                                               0x7c45d833aff07862L, 0xa5b1cfdba0ab4067L, 0x6ad047c430a12104L, 0x6c47bec883a7de39L, 0x944f6de09134dfb6L, 0x9aeba33ac6ecc6b0L, 0x52e762596bf68235L, 0x22af003ab672e811L,
                                               0x50065e535a213cf6L, 0xde0c89a556b9ae70L, 0xd1e0ccd25bb9c169L, 0x6b17b224bad6bf27L, 0x6b02e63195ad0cf8L, 0x455a4b4cfe30e3f5L, 0x9338e69c052b8e7bL, 0x5092ef950a16da0bL,
                                               0x67fef95d92607890L, 0x31865ced6120f37dL, 0x3a6853c7e70757a7L, 0x32ab0edb696703d3L, 0xee97f453f06791edL, 0x6dc93d9526a50e68L, 0x78edefd694af1eedL, 0x9c1169fa2777b874L,
                                               0x6bfa9aae5ec05779L, 0x371f77e76bb8417eL, 0x3550c2321fd6109cL, 0xfb4a3d794a9a80d2L, 0xf43c732873f24c13L, 0xaa9119ff184cccf4L, 0xb69e38a8965c6b65L, 0x1f2b1d1f15f6dc9cL,
                                               0xb5b4071dbfc73a66L, 0x8f9887e6078735a1L, 0x8de8a1c7797da9bL,  0xfcb6be43a9f2fe9bL, 0x49a7f41061a9e60L,  0x9f91508bffcfc14aL, 0xe3273522064480caL, 0xcd04f3ff001a4778L},

                                       {0x1bda0492e7e4586eL, 0xd23c8e176d113600L, 0x252f59cf0d9f04bbL, 0xb3598080ce64a656L, 0x993e1de72d36d310L, 0xa2853b80f17f58eeL, 0x1877b51e57a764d5L, 0x1f837cc7350524L,
                                               0x241260ed4ad1e87dL, 0x64c8e531bff53b55L, 0xca672b91e9e4fa16L, 0x3871700761b3f743L, 0xf95cffa23af5f6f4L, 0x8d14dedb30be846eL, 0x3b097adaf088f94eL, 0x21e0bd5026c619bfL,
                                               0xb8d91274b9e9d4fbL, 0x1db956e450275779L, 0x4fc8e9560f91b123L, 0x63573ff03e224774L, 0x647dfedcd894a29L,  0x7884d9bc6cb569d8L, 0x7fba195410e5ca30L, 0x106c09b972d2e822L,
                                               0x98f076a4f7a2322eL, 0x70cb6af7c2d5bcf0L, 0xb64be8d8b25396c1L, 0xa9aa4d20db084e9bL, 0x2e6d02c36017f67fL, 0xefed53d75fd64e6bL, 0xd9f1f30ccd97fb09L, 0xa2ebee47e2fbfce1L,
                                               0xfc87614baf287e07L, 0x240ab57a8b888b20L, 0xbf8d5108e27e0d48L, 0x61bdd1307c66e300L, 0xb925a6cd0421aff3L, 0x3e003e616a6591e9L, 0x94c3251f06f90cf3L, 0xbf84470805e69b5fL,
                                               0x758f450c88572e0bL, 0x1b6baca2ae4e125bL, 0x61cf4f94c97df93dL, 0x2738259634305c14L, 0xd39bb9c3a48db6cfL, 0x8215e577001332c8L, 0xa1082c0466df6c0aL, 0xef02cdd06ffdb432L,
                                               0x7976033a39f7d952L, 0x106f72fe81e2c590L, 0x8c90fd9b083f4558L, 0xfd080d236da814baL, 0x7b64978555326f9fL, 0x60e8ed72c0dff5d1L, 0xb063e962e045f54dL, 0x959f587d507a8359L,
                                               0x1a4e4822eb4d7a59L, 0x5d94337fbfaf7f5bL, 0xd30c088ba61ea5efL, 0x9d765e419fb69f6dL, 0x9e21f4f903b33fd9L, 0xb4d8f77bc3e56167L, 0x733ea705fae4fa77L, 0xa4ec0132764ca04bL}};
    ull king[2][64] = {{0x2102ae466ebb1148L, 0xe87fbb46217a360eL, 0x310cb380db6f7503L, 0xb5fdfc5d3132c498L, 0xdaf8e9829fe96b5fL, 0xcac09afbddd2cdb4L, 0xb862225b055b6960L, 0x55b6344cf97aafaeL,
                                              0x46e3ecaaf453ce9L,  0x962aceefa82e1c84L, 0xf5b4b0b0d2deeeb4L, 0x1af3dbe25d8f45daL, 0xf9f4892ed96bd438L, 0xc4c118bfe78feaaeL, 0x7a69afdcc42261aL,  0xf8549e1a3aa5e00dL,
                                              0x486289ddcc3d6780L, 0x222bbfae61725606L, 0x2bc60a63a6f3b3f2L, 0x177e00f9fc32f791L, 0x522e23f3925e319eL, 0x9c2ed44081ce5fbdL, 0x964781ce734b3c84L, 0xf05d129681949a4cL,
                                              0xd586bd01c5c217f6L, 0x233003b5a6cfe6adL, 0x24c0e332b70019b0L, 0x9da058c67844f20cL, 0xe4d9429322cd065aL, 0x1fab64ea29a2ddf7L, 0x8af38731c02ba980L, 0x7dc7785b8efdfc80L,
                                              0x93cbe0b699c2585dL, 0x1d95b0a5fcf90bc6L, 0x17efee45b0dee640L, 0x9e4c1269baa4bf37L, 0xd79476a84ee20d06L, 0xa56a5f0bfe39272L,  0x7eba726d8c94094bL, 0x5e5637885f29bc2bL,
                                              0xc61bb3a141e50e8cL, 0x2785338347f2ba08L, 0x7ca9723fbb2e8988L, 0xce2f8642ca0712dcL, 0x59300222b4561e00L, 0xc2b5a03f71471a6fL, 0xd5f9e858292504d5L, 0x65fa4f227a2b6d79L,
                                              0x71f1ce2490d20b07L, 0xe6c42178c4bbb92eL, 0xa9c32d5eae45305L,  0xc335248857fa9e7L,  0x142de49fff7a7c3dL, 0x64a53dc924fe7ac9L, 0x9f6a419d382595f4L, 0x150f361dab9dec26L,
                                              0xd20d8c88c8ffe65fL, 0x917f1dd5f8886c61L, 0x56986e2ef3ed091bL, 0x5fa7867caf35e149L, 0x81a1549fd6573da5L, 0x96fbf83a12884624L, 0xe728e8c83c334074L, 0xf1bcc3d275afe51aL},

                                      {0xd6b04d3b7651dd7eL, 0xe34a1d250e7a8d6bL, 0x53c065c6c8e63528L, 0x1bdea12e35f6a8c9L, 0x21874b8b4d2dbc4fL, 0x3a88a0fbbcb05c63L, 0x43ed7f5a0fae657dL, 0x230e343dfba08d33L,
                                              0xd4c718bc4ae8ae5fL, 0x9eedeca8e272b933L, 0x10e8b35af3eeab37L, 0xe09b88e1914f7afL,  0x3fa9ddfb67e2f199L, 0xb10bb459132d0a26L, 0x2c046f22062dc67dL, 0x5e90277e7cb39e2dL,
                                              0xb49b52e587a1ee60L, 0xac042e70f8b383f2L, 0x89c350c893ae7dc1L, 0xb592bf39b0364963L, 0x190e714fada5156eL, 0xec8177f83f900978L, 0x91b534f885818a06L, 0x81536d601170fc20L,
                                              0x57e3306d881edb4fL, 0xa804d18b7097475L,  0xe74733427b72f0c1L, 0x24b33c9d7ed25117L, 0xe805a1e290cf2456L, 0x3b544ebe544c19f9L, 0x3e666e6f69ae2c15L, 0xfb152fe3ff26da89L,
                                              0x1a4ff12616eefc89L, 0x990a98fd5071d263L, 0x84547ddc3e203c94L, 0x7a3aec79624c7daL,  0x8a328a1cedfe552cL, 0xd1e649de1e7f268bL, 0x2d8d5432157064c8L, 0x4ae7d6a36eb5dbcbL,
                                              0x4659d2b743848a2cL, 0x19ebb029435dcb0fL, 0x4e9d2827355fc492L, 0xccec0a73b49c9921L, 0x46c9feb55d120902L, 0x8d2636b81555a786L, 0x30c05b1ba332f41cL, 0xf6f7fd1431714200L,
                                              0xabbdcdd7ed5c0860L, 0x9853eab63b5e0b35L, 0x352787baa0d7c22fL, 0xc7f6aa2de59aea61L, 0x3727073c2e134b1L,  0x5a0f544dd2b1fb18L, 0x74f85198b05a2e7dL, 0x963ef2c96b33be31L,
                                              0xff577222c14f0a3aL, 0x4e4b705b92903ba4L, 0x730499af921549ffL, 0x13ae978d09fe5557L, 0xd9e92aa246bf719eL, 0x7a4c10ec2158c4a6L, 0x49cad48cebf4a71eL, 0xcf05daf5ac8d77b0L}};

    ull bishopZoneAttack[64][4] = {{9241421688590303744, 0,                 0,                 0},
                                   {36099303471055872,   0,                 0,                 256},
                                   {141012904183808,     0,                 0,                 66048},
                                   {550831656960,        0,                 0,                 16909312},
                                   {2151686144,          0,                 0,                 4328785920},
                                   {8404992,             0,                 0,                 1108169199616},
                                   {32768,               0,                 0,                 283691315109888},
                                   {0,                   0,                 0,                 72624976668147712},
                                   {4620710844295151616, 2,                 0,                 0},
                                   {9241421688590303232, 4,                 1,                 65536},
                                   {36099303471054848,   8,                 2,                 16908288},
                                   {141012904181760,     16,                4,                 4328783872},
                                   {550831652864,        32,                8,                 1108169195520},
                                   {2151677952,          64,                16,                283691315101696},
                                   {8388608,             128,               32,                72624976668131328},
                                   {0,                   0,                 64,                145249953336262656},
                                   {2310355422147510272, 516,               0,                 0},
                                   {4620710844295020544, 1032,              256,               16777216},
                                   {9241421688590041088, 2064,              513,               4328521728},
                                   {36099303470530560,   4128,              1026,              1108168671232},
                                   {141012903133184,     8256,              2052,              283691314053120},
                                   {550829555712,        16512,             4104,              72624976666034176},
                                   {2147483648,          32768,             8208,              145249953332068352},
                                   {0,                   0,                 16416,             290499906664136704},
                                   {1155177711056977920, 132104,            0,                 0},
                                   {2310355422113955840, 264208,            65536,             4294967296},
                                   {4620710844227911680, 528416,            131328,            1108101562368},
                                   {9241421688455823360, 1056832,           262657,            283691179835392},
                                   {36099303202095104,   2113664,           525314,            72624976397598720},
                                   {141012366262272,     4227072,           1050628,           145249952795197440},
                                   {549755813888,        8388608,           2101256,           290499905590394880},
                                   {0,                   0,                 4202512,           580999811180789760},
                                   {577588851233521664,  33818640,          0,                 0},
                                   {1155177702467043328, 67637280,          16777216,          1099511627776},
                                   {2310355404934086656, 135274560,         33619968,          283673999966208},
                                   {4620710809868173312, 270549120,         67240192,          72624942037860352},
                                   {9241421619736346624, 541097984,         134480385,         145249884075720704},
                                   {36099165763141632,   1082130432,        268960770,         290499768151441408},
                                   {140737488355328,     2147483648,        537921540,         580999536302882816},
                                   {0,                   0,                 1075843080,        1161999072605765632},
                                   {288793326105133056,  8657571872,        0,                 0},
                                   {577586652210266112,  17315143744,       4294967296,        281474976710656},
                                   {1155173304420532224, 34630287488,       8606711808,        72620543991349248},
                                   {2310346608841064448, 69260574720,       17213489152,       145241087982698496},
                                   {4620693217682128896, 138521083904,      34426978560,       290482175965396992},
                                   {9241386435364257792, 277025390592,      68853957121,       580964351930793984},
                                   {36028797018963968,   549755813888,      137707914242,      1161928703861587968},
                                   {0,                   0,                 275415828484,      2323857407723175936},
                                   {144115188075855872,  2216338399296,     0,                 0},
                                   {288230376151711744,  4432676798592,     1099511627776,     72057594037927936},
                                   {576460752303423488,  8865353596928,     2203318222848,     144115188075855872},
                                   {1152921504606846976, 17730707128320,    4406653222912,     288230376151711744},
                                   {2305843009213693952, 35461397479424,    8813306511360,     576460752303423488},
                                   {4611686018427387904, 70918499991552,    17626613022976,    1152921504606846976},
                                   {9223372036854775808, 140737488355328,   35253226045953,    2305843009213693952},
                                   {0,                   0,                 70506452091906,    4611686018427387904},
                                   {0,                   567382630219904,   0,                 0},
                                   {0,                   1134765260439552,  281474976710656,   0},
                                   {0,                   2269530520813568,  564049465049088,   0},
                                   {0,                   4539061024849920,  1128103225065472,  0},
                                   {0,                   9078117754732544,  2256206466908160,  0},
                                   {0,                   18155135997837312, 4512412933881856,  0},
                                   {0,                   36028797018963968, 9024825867763968,  0},
                                   {0,                   0,                 18049651735527937, 0}
    };

    ull rookZoneAttack[64][4] = {{72340172838076672,   254,                  0,                 0},
                                 {144680345676153344,  252,                  0,                 1},
                                 {289360691352306688,  248,                  0,                 3},
                                 {578721382704613376,  240,                  0,                 7},
                                 {1157442765409226752, 224,                  0,                 15},
                                 {2314885530818453504, 192,                  0,                 31},
                                 {4629771061636907008, 128,                  0,                 63},
                                 {9259542123273814016, 0,                    0,                 127},
                                 {72340172838076416,   65024,                1,                 0},
                                 {144680345676152832,  64512,                2,                 256},
                                 {289360691352305664,  63488,                4,                 768},
                                 {578721382704611328,  61440,                8,                 1792},
                                 {1157442765409222656, 57344,                16,                3840},
                                 {2314885530818445312, 49152,                32,                7936},
                                 {4629771061636890624, 32768,                64,                16128},
                                 {9259542123273781248, 0,                    128,               32512},
                                 {72340172838010880,   16646144,             257,               0},
                                 {144680345676021760,  16515072,             514,               65536},
                                 {289360691352043520,  16252928,             1028,              196608},
                                 {578721382704087040,  15728640,             2056,              458752},
                                 {1157442765408174080, 14680064,             4112,              983040},
                                 {2314885530816348160, 12582912,             8224,              2031616},
                                 {4629771061632696320, 8388608,              16448,             4128768},
                                 {9259542123265392640, 0,                    32896,             8323072},
                                 {72340172821233664,   4261412864,           65793,             0},
                                 {144680345642467328,  4227858432,           131586,            16777216},
                                 {289360691284934656,  4160749568,           263172,            50331648},
                                 {578721382569869312,  4026531840,           526344,            117440512},
                                 {1157442765139738624, 3758096384,           1052688,           251658240},
                                 {2314885530279477248, 3221225472,           2105376,           520093696},
                                 {4629771060558954496, 2147483648,           4210752,           1056964608},
                                 {9259542121117908992, 0,                    8421504,           2130706432},
                                 {72340168526266368,   1090921693184,        16843009,          0},
                                 {144680337052532736,  1082331758592,        33686018,          4294967296},
                                 {289360674105065472,  1065151889408,        67372036,          12884901888},
                                 {578721348210130944,  1030792151040,        134744072,         30064771072},
                                 {1157442696420261888, 962072674304,         269488144,         64424509440},
                                 {2314885392840523776, 824633720832,         538976288,         133143986176},
                                 {4629770785681047552, 549755813888,         1077952576,        270582939648},
                                 {9259541571362095104, 0,                    2155905152,        545460846592},
                                 {72339069014638592,   279275953455104,      4311810305,        0},
                                 {144678138029277184,  277076930199552,      8623620610,        1099511627776},
                                 {289356276058554368,  272678883688448,      17247241220,       3298534883328},
                                 {578712552117108736,  263882790666240,      34494482440,       7696581394432},
                                 {1157425104234217472, 246290604621824,      68988964880,       16492674416640},
                                 {2314850208468434944, 211106232532992,      137977929760,      34084860461056},
                                 {4629700416936869888, 140737488355328,      275955859520,      69269232549888},
                                 {9259400833873739776, 0,                    551911719040,      139637976727552},
                                 {72057594037927936,   71494644084506624,    1103823438081,     0},
                                 {144115188075855872,  70931694131085312,    2207646876162,     281474976710656},
                                 {288230376151711744,  69805794224242688,    4415293752324,     844424930131968},
                                 {576460752303423488,  67553994410557440,    8830587504648,     1970324836974592},
                                 {1152921504606846976, 63050394783186944,    17661175009296,    4222124650659840},
                                 {2305843009213693952, 54043195528445952,    35322350018592,    8725724278030336},
                                 {4611686018427387904, 36028797018963968,    70644700037184,    17732923532771328},
                                 {9223372036854775808, 0,                    141289400074368,   35747322042253312},
                                 {0,                   18302628885633695744, 282578800148737,   0},
                                 {0,                   18158513697557839872, 565157600297474,   72057594037927936},
                                 {0,                   17870283321406128128, 1130315200594948,  216172782113783808},
                                 {0,                   17293822569102704640, 2260630401189896,  504403158265495552},
                                 {0,                   16140901064495857664, 4521260802379792,  1080863910568919040},
                                 {0,                   13835058055282163712, 9042521604759584,  2233785415175766016},
                                 {0,                   9223372036854775808,  18085043209519168, 4539628424389459968},
                                 {0,                   0,                    36170086419038336, 9151314442816847872}
    };
    ull whiteKingSideCastling = 0x31d71dce64b2c310L;
    ull whiteQueenSideCastling = 0xf165b587df898190L;
    ull blackKingSideCastling = 0xa57e6339dd2cf3a0L;
    ull blackQueenSideCastling = 0x1ef6e6dbb1961ec9L;
    ull passantColumn[8] = {0x70cc73d90bc26e24L, 0xe21a6b35df0c3ad7L, 0x3a93d8b2806962L,
                                           0x1c99ded33cb890a1L, 0xcf3145de0add4289L, 0xd0e4427a5514fb72L,
                                           0x77c621cc9fb3a483L, 0x67a34dac4356550bL};
    ull whiteMove = 0xf8d626aaaf278509L;

    // board representation

    ull whitePawns;
    ull whiteKnights;
    ull whiteBishops;
    ull whiteRooks;
    ull whiteQueens;
    ull whiteKing;

    ull blackPawns;
    ull blackKnights;
    ull blackBishops;
    ull blackRooks;
    ull blackQueens;
    ull blackKing;

    ull whitePieces;
    ull blackPieces;
    ull allPieces;

    bool drawState = false;
    ull key; // zobrist key

    ull keyHistory[MAX_GAME_LENGTH];
    ull whitePawnHistory[MAX_GAME_LENGTH];
    ull whiteKnightHistory[MAX_GAME_LENGTH];
    ull whiteBishopHistory[MAX_GAME_LENGTH];
    ull whiteRookHistory[MAX_GAME_LENGTH];
    ull whiteQueenHistory[MAX_GAME_LENGTH];
    ull whiteKingHistory[MAX_GAME_LENGTH];

    ull blackPawnHistory[MAX_GAME_LENGTH];
    ull blackKnightHistory[MAX_GAME_LENGTH];
    ull blackBishopHistory[MAX_GAME_LENGTH];
    ull blackRookHistory[MAX_GAME_LENGTH];
    ull blackQueenHistory[MAX_GAME_LENGTH];
    ull blackKingHistory[MAX_GAME_LENGTH];

    ull whitePiecesHistory[MAX_GAME_LENGTH];
    ull blackPiecesHistory[MAX_GAME_LENGTH];
    ull allPiecesHistory[MAX_GAME_LENGTH];

    //bool whiteTomoveHistory;
    int fiftyMoveRuleHistory[MAX_GAME_LENGTH];
    int enPassantLocHistory[MAX_GAME_LENGTH];
    int moveHistory[MAX_GAME_LENGTH];
    //char pieceArray_history[MAX_GAME_LENGTH][MAX_GAME_LENGTH];
    bool whiteCastleKHistory[MAX_GAME_LENGTH];
    bool whiteCastleQHistory[MAX_GAME_LENGTH];
    bool blackCastleKHistory[MAX_GAME_LENGTH];
    bool blackCastleQHistory[MAX_GAME_LENGTH];
    bool whiteHasCastledHistory[MAX_GAME_LENGTH];
    bool blackHasCastledHistory[MAX_GAME_LENGTH];



    //should be considered at implementation
    ull whiteCastleK;
    ull whiteCastleQ;
    ull blackCastleK;
    ull blackCastleQ;
    ull enPassantLoc;
    bool whiteToMove = true;

    vector<int> allValidMoves;
    vector<int> kingCheckers;

    int moveNumber = 0;
    int fiftyMoveRule = 0;

/**********************************************************************************************************************
*                                               Optmization functions                                                 *
**********************************************************************************************************************/
    void disp(){

        char arr[8][8];
        memset(arr,0,sizeof(arr));
        int Cnt = __builtin_popcountll(allPieces);
        ull wp = allPieces;
        while(wp) {
            int ind = (log2(wp & -wp) + EPS);
            wp -= (wp & -wp);
            if(whitePawns & (1ull<<ind)){
                arr[ind/8][ind%8] = 'P';
            }
            if(whiteBishops & (1ull<<ind)){
                arr[ind/8][ind%8] = 'B';
            }
            if(whiteKnights & (1ull<<ind)){
                arr[ind/8][ind%8] = 'N';
            }
            if(whiteKing & (1ull<<ind)){
                arr[ind/8][ind%8] = 'K';
            }
            if(whiteQueens & (1ull<<ind)){
                arr[ind/8][ind%8] = 'Q';
            }
            if(whiteRooks & (1ull<<ind)){
                arr[ind/8][ind%8] = 'R';
            }
            if(blackPawns & (1ull<<ind)){
                arr[ind/8][ind%8] = 'p';
            }
            if(blackBishops & (1ull<<ind)){
                arr[ind/8][ind%8] = 'b';
            }
            if(blackKnights & (1ull<<ind)){
                arr[ind/8][ind%8] = 'n';
            }
            if(blackKing & (1ull<<ind)){
                arr[ind/8][ind%8] = 'k';
            }
            if(blackQueens & (1ull<<ind)){
                arr[ind/8][ind%8] = 'q';
            }
            if(blackRooks & (1ull<<ind)){
                arr[ind/8][ind%8] = 'r';
            }

        }
        for (int i = 7; i >= 0; i--){
            for (int j = 0; j < 8; j++){
                cout<<arr[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void fenInterpreter(string fen){
        whiteRooks = 0;
        whiteQueens = 0;
        whiteKing = 0;
        whiteKnights = 0;
        whiteBishops = 0;
        whitePawns = 0;
        whitePieces = 0;

        blackRooks = 0;
        blackQueens = 0;
        blackKing = 0;
        blackKnights = 0;
        blackBishops = 0;
        blackPawns = 0;
        blackPieces = 0;
        allPieces = 0;
        int file = 1;
        int rank = 8;
        for (int i = 0; i < fen.size(); i++){
            if(fen[i] == ' ')break;
            if(fen[i] == '/'){if(file != 9)rank--; file = 1;  continue;}
            if(isdigit(fen[i])){file += (fen[i] - '0')-1;}
            if(fen[i] == 'p'){blackPawns |= (1ull << ((rank-1)*8 + (file-1)));}
            if(fen[i] == 'n'){blackKnights |= (1ull << ((rank-1)*8 + (file-1)));}
            if(fen[i] == 'r'){blackRooks |= (1ull << ((rank-1)*8 + (file-1)));}
            if(fen[i] == 'q'){blackQueens |= (1ull << ((rank-1)*8 + (file-1)));}
            if(fen[i] == 'k'){blackKing |= (1ull << ((rank-1)*8 + (file-1)));}
            if(fen[i] == 'b'){blackBishops |= (1ull << ((rank-1)*8 + (file-1)));}

            if(fen[i] == 'P'){whitePawns |= (1ull << ((rank-1)*8 + (file-1)));  }
            if(fen[i] == 'N'){whiteKnights |= (1ull << ((rank-1)*8 + (file-1)));}
            if(fen[i] == 'R'){whiteRooks |= (1ull << ((rank-1)*8 + (file-1)));}
            if(fen[i] == 'Q'){whiteQueens |= (1ull << ((rank-1)*8 + (file-1)));}
            if(fen[i] == 'K'){whiteKing |= (1ull << ((rank-1)*8 + (file-1)));}
            if(fen[i] == 'B'){whiteBishops |= (1ull << ((rank-1)*8 + (file-1)));}
            file++;
            if(file == 9){rank--;}
        }


        blackPieces = blackPawns | blackBishops | blackKing | blackKnights | blackQueens | blackRooks;
        whitePieces = whitePawns | whiteBishops | whiteKing | whiteKnights | whiteQueens | whiteRooks;
        allPieces = whitePieces | blackPieces;
        //this function is not complete yet a7ba2i fellah
    }


    char getPieceAt(int loc) {
        if (allPieces & (1ULL << loc)) {
            if (whitePawns & (1ULL << loc)) return 'P';
            else if (whiteBishops & (1ULL << loc)) return 'B';
            else if (whiteKing & (1ULL << loc)) return 'K';
            else if (whiteKnights & (1ULL << loc)) return 'N';
            else if (whiteQueens & (1ULL << loc)) return 'Q';
            else if (whiteRooks & (1ULL << loc)) return 'R';
            else if (blackPawns & (1ULL << loc)) return 'p';
            else if (blackBishops & (1ULL << loc)) return 'b';
            else if (blackKing & (1ULL << loc)) return 'k';
            else if (blackKnights & (1ULL << loc)) return 'n';
            else if (blackQueens & (1ULL << loc)) return 'q';
            else if (blackRooks & (1ULL << loc)) return 'r';
        }
        return 0;
    };


    // Zobrist hash generators
    ull squareZKey(int location, char piece) {
        switch (piece) {
            case 'p':
                return pawn[0][location];
            case 'P':
                return pawn[1][location];
            case 'n':
                return knight[0][location];
            case 'N':
                return knight[1][location];
            case 'b':
                return bishop[0][location];
            case 'B':
                return bishop[1][location];
            case 'r':
                return rook[0][location];
            case 'R':
                return rook[1][location];
            case 'q':
                return queen[0][location];
            case 'Q':
                return queen[1][location];
            case 'k':
                return king[0][location];
            case 'K':
                return king[1][location];
        }
        return 0;
    }

    ull ZMove(int from, int to, char piece) {
        return squareZKey(from, piece) ^ squareZKey(to, piece);
    }

    ull ZBoard() {
        ull key = 0;

        for (int loc = 0; loc < 64; loc++) {
            key ^= squareZKey(loc, getPieceAt(loc));
        }

        if (whiteCastleK)
            key ^= whiteKingSideCastling;
        if (whiteCastleQ)
            key ^= whiteQueenSideCastling;
        if (blackCastleK)
            key ^= blackKingSideCastling;
        if (blackCastleQ)
            key ^= blackQueenSideCastling;

        if (enPassantLoc != -1)
            key ^= passantColumn[getColumn(enPassantLoc)];

        if (whiteToMove)
            key ^= whiteMove;

        return key;
    }

    bool locExist(ull mask, ull check) {
        return (mask & check) != 0;
    }

    void unsetBit(ull &mask, ull bit) {
        mask &= (~(bit));
    }

    bool isCellInRow(int rowNum, int cell) {
        return cell >= 4 * rowNum && cell < 4 * (rowNum + 1);
    }

    int getColumn(int cellNum) {
        return cellNum % 8;
    }

    ull getLSB(ull x) {
        return x & -x;
    }


/**********************************************************************************************************************
*                                          board representation functions                                             *
**********************************************************************************************************************/

//==================================================Make Move(doo)
    void doo(int move) {
        if (whiteCastleK)
            key ^= whiteKingSideCastling;
        if (whiteCastleQ)
            key ^= whiteQueenSideCastling;
        if (blackCastleK)
            key ^= blackKingSideCastling;
        if (blackCastleQ)
            key ^= blackQueenSideCastling;

        if (enPassantLoc != -1)
            key ^= passantColumn[getColumn(enPassantLoc)];

        if (whiteToMove)
            key ^= whiteMove;

        int specialEvent = move & 7;
        int capture = move & 8;
        int type = move & 112;
        int from = move & 8064;
        int to = move & 516096;

        int moveXor = (1ull << from) ^(1ull << to);
        // pawn 0
        // knight 1
        // bishop 2
        // rook 3
        // queen 4
        // king 5

        switch (type) {
            case 0:
                if (specialEvent == PROMOTEBISHOP || specialEvent == PROMOTEKNIGHT || specialEvent == PROMOTEQUEEN ||
                    specialEvent == PROMOTEROOK)
                    whitePawns ^= from, key ^= squareZKey(from, 'p');
                else
                    whitePawns ^= moveXor, key ^= ZMove(from, to, 'p');
                if (specialEvent == PROMOTEBISHOP)
                    whiteBishops ^= to, key ^= squareZKey(to, 'b');
                else if (specialEvent == PROMOTEKNIGHT)
                    whiteKnights ^= to, key ^= squareZKey(to, 'n');
                else if (specialEvent == PROMOTEROOK)
                    whiteRooks ^= to, key ^= squareZKey(to, 'r');
                else if (specialEvent == PROMOTEQUEEN)
                    whiteQueens ^= to, key ^= squareZKey(to, 'q');
                break;
            case 1:
                whiteKnights ^= moveXor;
                key ^= ZMove(from, to, 'n');
                break;
            case 2:
                whiteBishops ^= moveXor;
                key ^= ZMove(from, to, 'b');
                break;
            case 3:
                whiteRooks ^= moveXor;
                key ^= ZMove(from, to, 'r');
                break;
            case 4:
                whiteQueens ^= moveXor;
                key ^= ZMove(from, to, 'q');
                break;
            case 5:
                whiteKing ^= moveXor;
                if (specialEvent == CASTLEKINGSIDE)
                    whiteRooks ^= 160, whiteCastleK = 1;
                else if (specialEvent == CASTLEQUEENSIDE)
                    whiteRooks ^= 9, whiteCastleQ = 1;
                key ^= ZMove(from, to, 'k');
                break;
            default:
                break;
        }

        whitePieces = whitePawns | whiteKnights | whiteBishops | whiteQueens | whiteKing | whiteRooks;

        if (capture) {
            if (locExist(blackPawns, 1ull << to)) {
                unsetBit(blackPawns, 1ull << to);
                key ^= squareZKey(to, 'P');
            } else if (~enPassantLoc && type == 0 && to == enPassantLoc + 40 &&
                       isCellInRow(4, from) &&
                       (getColumn(from) == enPassantLoc - 1 || getColumn(from) == enPassantLoc + 1)) {
                unsetBit(blackPawns, 1ull << to);
                key ^= squareZKey(to, 'P');
            } else if (locExist(blackKnights, 1ull << to)) {
                unsetBit(blackKnights, 1ull << to);
                key ^= squareZKey(to, 'N');
            } else if (locExist(blackBishops, 1ull << to)) {
                unsetBit(blackBishops, 1ull << to);
                key ^= squareZKey(to, 'B');
            } else if (locExist(blackQueens, 1ull << to)) {
                unsetBit(blackQueens, 1ull << to);
                key ^= squareZKey(to, 'Q');
            }

            blackPieces = blackPawns | blackKnights | blackBishops | blackQueens | blackKing | blackRooks;
        }

        allPieces = whitePieces | blackPieces;

        if (specialEvent == ENPASSANT)
            enPassantLoc = 3;

        else enPassantLoc = -1;

        if (whiteCastleK)
            key ^= whiteKingSideCastling;
        if (whiteCastleQ)
            key ^= whiteQueenSideCastling;
        if (blackCastleK)
            key ^= blackKingSideCastling;
        if (blackCastleQ)
            key ^= blackQueenSideCastling;

        if (enPassantLoc != -1)
            key ^= passantColumn[getColumn(enPassantLoc)];

        if (whiteToMove)
            key ^= whiteMove;


        //handling fiftyMoveRule
        if (type != 0 && capture == 0)
            fiftyMoveRule++;
        else
            fiftyMoveRule = 0;

        //saving all of our history
        saveHistory();
        moveNumber++;

        //three same moves
        zobristTable[key]++;
        if (zobristTable[key] >= 3)
            drawState = true;

        //switch turns
        whiteToMove = !whiteToMove;

    }

//==================================================Saving history, Undo
    void saveHistory() {
        whitePawnHistory[moveNumber] = whitePawns;
        whiteKnightHistory[moveNumber] = whiteKnights;
        whiteBishopHistory[moveNumber] = whiteBishops;
        whiteRookHistory[moveNumber] = whiteRooks;
        whiteQueenHistory[moveNumber] = whiteQueens;
        whiteKingHistory[moveNumber] = whiteKing;
        blackPawnHistory[moveNumber] = blackPawns;
        blackKnightHistory[moveNumber] = blackKnights;
        blackBishopHistory[moveNumber] = blackBishops;
        blackRookHistory[moveNumber] = blackRooks;
        blackQueenHistory[moveNumber] = blackQueens;
        blackKingHistory[moveNumber] = blackKing;
        whitePiecesHistory[moveNumber] = whitePieces;
        blackPiecesHistory[moveNumber] = blackPieces;
        allPiecesHistory[moveNumber] = allPieces;
        //white_to_moveHistory[moveNumber] = white_to_move;
        fiftyMoveRuleHistory[moveNumber] = fiftyMoveRule;
        enPassantLocHistory[moveNumber] = enPassantLoc;
        //moveHistory[moveNumber] = move;
//        white_castle_k_history[moveNumber] = white_castle_k;
//        white_castle_q_history[moveNumber] = white_castle_q;
//        black_castle_k_history[moveNumber] = black_castle_k;
//        black_castle_q_history[moveNumber] = black_castle_q;
        keyHistory[moveNumber] = key;
    }

    void undoo() {

        if (fiftyMoveRule != 0)
            fiftyMoveRule--;

        if (zobristTable[key] == 3) {
            drawState = false;
            zobristTable[key]--;
        }

        moveNumber--;

        whitePawns = whitePawnHistory[moveNumber];
        whiteKnights = whiteKnightHistory[moveNumber];
        whiteBishops = whiteBishopHistory[moveNumber];
        whiteRooks = whiteRookHistory[moveNumber];
        whiteQueens = whiteQueenHistory[moveNumber];
        whiteKing = whiteKingHistory[moveNumber];
        blackPawns = blackPawnHistory[moveNumber];
        blackKnights = blackKnightHistory[moveNumber];
        blackBishops = blackBishopHistory[moveNumber];
        blackRooks = blackRookHistory[moveNumber];
        blackQueens = blackQueenHistory[moveNumber];
        blackKing = blackKingHistory[moveNumber];
        whitePieces = whitePiecesHistory[moveNumber];
        blackPieces = blackPiecesHistory[moveNumber];
        allPieces = allPiecesHistory[moveNumber];
        //white_to_moveHistory[moveNumber] = white_to_move;
        fiftyMoveRule = fiftyMoveRuleHistory[moveNumber];
        enPassantLoc = enPassantLocHistory[moveNumber];
        //move = moveHistory[moveNumber];
//        whiteCastleK = white_castle_k_history[moveNumber];
//        whiteCastleQ = white_castle_q_history[moveNumber];
//        blackCastleK = black_castle_k_history[moveNumber];
//        blackCastleQ = black_castle_q_history[moveNumber];
        key = keyHistory[moveNumber];

    }

//==================================================Draw, Mate, Check, EndOfGame, EndGame, Pass

    bool isDraw() {

        // stale
//        int current_moves[] = new int current_moves[MAX_MOVES];
//        if (MoveGenerator.getAllLegalMoves(this, current_moves) == 0 && !isCheck())
//            return true;

        // 50mr
        if (fiftyMoveRule >= 50)
            return true;

        // threefold rep
        if (drawState)
            return true;

        // insufficient material -- so far only Kk, but need to add:
        if ((whitePieces & ~whiteKing) == 0 && (blackPieces & ~blackKing) == 0)
            return true;

        return false;
    }

    bool isMate() {
//        if(kingMoves.size() == 0 && isCheck())
//            return true;
//        else
//            return false;
    }

    bool isCheck() {
        //if the destination of any valid moves is at king`s position
        bool threat = false;
        for(int i= 0; i< allValidMoves.size();i++){

            int to = allValidMoves[i] & 516096;
            int x = (ull(to) & whiteKing) | (ull(to) & blackKing);

            if(x) {
                kingCheckers.push_back(allValidMoves[i]);
                threat = true;
            }
        }
        return threat;
    }

    bool isEndOfGame() { return (isMate() || isDraw()); }

    bool isEndGame() {
        // q == 0 ||
        // .... ((q == 1 && n == 1 && b == 0 && r == 0)
        // .... || (q == 1 && n == 0 && b == 1 && r == 0))
        int q = __builtin_popcountll(whiteQueens);
        int n = __builtin_popcountll(whiteKnights);
        int b = __builtin_popcountll(whiteBishops);
        int r = __builtin_popcountll(whiteRooks);
        bool white_endgame =
                (q == 0 && r <= 1)
                || ((q == 1 && n == 1 && b == 0 && r == 0) || (q == 1 && n == 0
                                                               && b == 1 && r == 0));

        q = __builtin_popcountll(blackQueens);
        n = __builtin_popcountll(blackKnights);
        b = __builtin_popcountll(blackBishops);
        r = __builtin_popcountll(blackRooks);

        bool black_endgame =
                (q == 0 && r <= 1)
                || ((q == 1 && n == 1 && b == 0 && r == 0) || (q == 1 && n == 0
                                                               && b == 1 && r == 0));

        return white_endgame && black_endgame;
    }

    void pass() {
        saveHistory();
        moveNumber++;
        if (enPassantLoc != -1)
            key ^= passantColumn[getColumn(enPassantLoc)];
        enPassantLoc = -1;
        whiteToMove = !whiteToMove;
        key ^= whiteMove;


    }


/**********************************************************************************************************************
 *                                               Valid Moves                                                           *
 **********************************************************************************************************************/

//==================================================WhitePawn valid Moves

    vector<int> whitePawnVMGen() {
        vector<int> whitePawnVM, whitePawnCap;
        int pawnCnt = __builtin_popcountll(whitePawns);
        ull wp = whitePawns;
        while (pawnCnt--) {
            int ind = (log2(wp&-wp) + EPS);
            wp-=(wp&-wp);
            if(ind >= 8 && ind <= 15){//move two squares forward --> +16
                int newInd = ind + 16;
                if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))&& !(allPieces&(1ull << (newInd-8)))){
                    //new valid move from ind to newInd
                    int flag = 0;
                    if((getColumn(ind + 1) != 0) && blackPawns&(newInd+1)) flag = 3;
                    if((getColumn(ind - 1) != 7) && blackPawns&(newInd-1)) flag = 3;
                    whitePawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | ( 0 << 15) | (flag << 16));
                }
            }
            //move one square forward --> +8
            int newInd = ind + 8;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                //new valid move from ind to newInd
                if(newInd > 55) {
                    whitePawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | (0 << 15) | (4 << 16));
                    whitePawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | (0 << 15) | (5 << 16));
                    whitePawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | (0 << 15) | (6 << 16));
                    whitePawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | (0 << 15) | (7 << 16));
                }else whitePawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | (0 << 15) | (0 << 16));
            }

            //captures --> +7 & +9
            newInd = ind + 7;
            if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                //new valid capture from ind to newInd
                if(newInd > 55) {
                    whitePawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (4 << 16));
                    whitePawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (5 << 16));
                    whitePawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (6 << 16));
                    whitePawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (7 << 16));
                }else whitePawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (0 << 16));
            }
            newInd = ind + 9;
            if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                //new valid capture from ind to newInd
                if(newInd > 55) {
                    whitePawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (4 << 16));
                    whitePawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (5 << 16));
                    whitePawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (6 << 16));
                    whitePawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (7 << 16));
                }else whitePawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (0 << 16));

            }
        }
        std::vector<int> ret = whitePawnVM;
        ret.insert(ret.end(), whitePawnCap.begin(), whitePawnCap.end());
        return ret;

    }

//==================================================BlackPawn valid Moves

    vector<int> blackPawnVMGen() {
        vector<int> blackPawnVM, blackPawnCap;
        int pawnCnt = __builtin_popcountll(blackPawns);
        ull wp = blackPawns;
        while (pawnCnt--) {
            int ind = (log2(wp&-wp) + EPS);
            wp-=(wp&-wp);
            if(ind >= 48 && ind <= 55){//move two squares forward --> +16
                int newInd = ind - 16;
                if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd)) && !(allPieces&(1ull << (newInd+8)))){
                    //new valid move from ind to newInd
                    int flag = 0;
                    if((getColumn(ind + 1) != 0) && whitePawns&(newInd+1)) flag = 3;
                    if((getColumn(ind - 1) != 7) && whitePawns&(newInd-1)) flag = 3;
                    blackPawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | ( 0 << 15) | (flag << 16) | (1 << 20));
                }
            }
            //move one square forward --> +8
            int newInd = ind - 8;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                //new valid move from ind to newInd
                if(newInd < 8) {
                    blackPawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | (0 << 15) | (4 << 16) | (1 << 20));
                    blackPawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | (0 << 15) | (5 << 16) | (1 << 20));
                    blackPawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | (0 << 15) | (6 << 16) | (1 << 20));
                    blackPawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | (0 << 15) | (7 << 16) | (1 << 20));
                }else blackPawnVM.push_back((ind) | (newInd << 6) | (0 << 12) | (0 << 15) | (0 << 16) | (1 << 20));
            }

            //captures --> +7 & +9
            newInd = ind - 7;
            if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                //new valid capture from ind to newInd
                if(newInd < 8) {
                    blackPawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (4 << 16) | (1 << 20));
                    blackPawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (5 << 16) | (1 << 20));
                    blackPawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (6 << 16) | (1 << 20));
                    blackPawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (7 << 16) | (1 << 20));
                }else blackPawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (0 << 16) | (1 << 20));
            }
            newInd = ind - 9;
            if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                //new valid capture from ind to newInd
                if(newInd < 8) {
                    blackPawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (4 << 16) | (1 << 20));
                    blackPawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (5 << 16) | (1 << 20));
                    blackPawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (6 << 16) | (1 << 20));
                    blackPawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (7 << 16) | (1 << 20));
                }else blackPawnCap.push_back((ind) | (newInd << 6) | (0 << 12) | (1 << 15) | (0 << 16) | (1 << 20));

            }
        }
        std::vector<int> ret = blackPawnVM;
        ret.insert(ret.end(), blackPawnCap.begin(), blackPawnCap.end());
        return ret;

    }

//==================================================WhiteKnight valid Moves
    vector<int> whiteKnightVMGen(){
        vector<int> whiteKnightVM;
        vector<int> whiteKnightCap;
        int knightCnt = __builtin_popcountll(whiteKnights);
        ull wp = whiteKnights;
        while(knightCnt--){
            int ind = (log2(wp&-wp) + EPS);
            wp-=(wp&-wp);
            int newInd = ind + 6;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                whiteKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16));
            }else if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                whiteKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16));
            }
            newInd = ind + 10;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                whiteKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16));
            }else if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                whiteKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16));
            }
            newInd = ind + 15;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                whiteKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16));
            }else if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                whiteKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16));
            }
            newInd = ind + 17;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                whiteKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16));
            }else if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                whiteKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16));
            }




            newInd = ind - 6;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                whiteKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16));
            }else if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                whiteKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16));
            }
            newInd = ind - 10;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                whiteKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16));
            }else if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                whiteKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16));
            }
            newInd = ind - 15;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                whiteKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16));
            }else if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                whiteKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16));
            }
            newInd = ind - 17;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                whiteKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16));
            }else if((newInd>=0 && newInd<=63) && (blackPieces&(1ull << newInd))){
                whiteKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16));
            }

        }
        std::vector<int> ret = whiteKnightVM;
        ret.insert(ret.end(), whiteKnightCap.begin(), whiteKnightCap.end());
        return ret;


    }

//==================================================BlackKnight valid Moves
    vector <int> blackKnightVMGen(){
        vector<int> blackKnightVM, blackKnightCap;
        int knightCnt = __builtin_popcountll(blackKnights);
        ull wp = blackKnights;
        while(knightCnt--){
            int ind = (log2(wp&-wp) + EPS);
            wp-=(wp&-wp);
            int newInd = ind + 6;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                blackKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16) | (1 << 20));
            }else if((newInd>=0 && newInd<=63) && (whitePieces&(1ull << newInd))){
                blackKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16) | (1 << 20));
            }
            newInd = ind + 10;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                blackKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16) | (1 << 20));
            }else if((newInd>=0 && newInd<=63) && (whitePieces&(1ull << newInd))){
                blackKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16) | (1 << 20));
            }
            newInd = ind + 15;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                blackKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16) | (1 << 20));
            }else if((newInd>=0 && newInd<=63) && (whitePieces&(1ull << newInd))){
                blackKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16) | (1 << 20));
            }
            newInd = ind + 17;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                blackKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16) | (1 << 20));
            }else if((newInd>=0 && newInd<=63) && (whitePieces&(1ull << newInd))){
                blackKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16) | (1 << 20));
            }




            newInd = ind - 6;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                blackKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16) | (1 << 20));
            }else if((newInd>=0 && newInd<=63) && (whitePieces&(1ull << newInd))){
                blackKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16) | (1 << 20));
            }
            newInd = ind - 10;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                blackKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16) | (1 << 20));
            }else if((newInd>=0 && newInd<=63) && (whitePieces&(1ull << newInd))){
                blackKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16) | (1 << 20));
            }
            newInd = ind - 15;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                blackKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16) | (1 << 20));
            }else if((newInd>=0 && newInd<=63) && (whitePieces&(1ull << newInd))){
                blackKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16) | (1 << 20));
            }
            newInd = ind - 17;
            if((newInd>=0 && newInd<=63) && !(allPieces&(1ull << newInd))){
                blackKnightVM.push_back((ind) | (newInd << 6) | (1 << 12) | (0 << 15) | (0 << 16) | (1 << 20));
            }else if((newInd>=0 && newInd<=63) && (whitePieces&(1ull << newInd))){
                blackKnightCap.push_back((ind) | (newInd << 6) | (1 << 12) | (1 << 15) | (0 << 16) | (1 << 20));
            }

        }
        std::vector<int> ret = blackKnightVM;
        ret.insert(ret.end(), blackKnightCap.begin(), blackKnightCap.end());
        return ret;
    }

//==================================================Rook valid Moves

    vector<int> rookMoves() {
        vector<int> ret;
        ull tmpWhiteRooks = whiteRooks;
        while (tmpWhiteRooks) {
            ull locRaisedPow = getLSB(tmpWhiteRooks);
            tmpWhiteRooks -= locRaisedPow;
            int loc = log2(locRaisedPow) + EPS;
            int lim[] = {64, (loc / 8 + 1) * 8, -1, loc / 8 * 8};
            int dx[] = {8, 1, -8, -1};
            for (int i = 0; i < 2; ++i) {
                ull mask = rookZoneAttack[loc][i];
                ull res = allPieces & mask;
                ull firstCollision = getLSB(res);
                bool noCollision = firstCollision == 0;
                int firstCollisionCell = log2(firstCollision) + EPS;
                for (int j = loc + dx[i]; j < lim[i] && (j < firstCollisionCell || noCollision); j += dx[i]) {

                }
            }
        }
    }


};