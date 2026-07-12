extern "C" MtxF* sMatrixStack;
extern "C" MtxF* sCurrentMatrix;
extern "C" LightsBuffer sLightsBuffer;
extern "C" s16 sWarpTimerTarget;
extern "C" MapMarkData** sLoadedMarkDataTable;

//Camera static data
extern "C" int32_t sInitRegs;
extern "C" int32_t gDbgCamEnabled;
extern "C" int32_t sDbgModeIdx;
extern "C" int16_t sNextUID;
extern "C" int32_t sCameraInterfaceFlags;
extern "C" int32_t sCameraInterfaceAlpha;
extern "C" int32_t sCameraShrinkWindowVal;
extern "C" int32_t D_8011D3AC;
extern "C" int32_t sDemo5PrevAction12Frame;
extern "C" int32_t sDemo5PrevSfxFrame;
extern "C" int32_t D_8011D3F0;
extern "C" OnePointCsFull D_8011D6AC[];
extern "C" OnePointCsFull D_8011D724[];
extern "C" OnePointCsFull D_8011D79C[];
extern "C" OnePointCsFull D_8011D83C[];
extern "C" OnePointCsFull D_8011D88C[];
extern "C" OnePointCsFull D_8011D8DC[];
extern "C" OnePointCsFull D_8011D954[];
extern "C" OnePointCsFull D_8011D9F4[]; 
extern "C" int16_t depthPhase;
extern "C" int16_t screenPlanePhase;
extern "C" int32_t sOOBTimer;
extern "C" f32 D_8015CE50;
extern "C" f32 D_8015CE54;
extern "C" CamColChk D_8015CE58;

//Gameover
extern "C" uint16_t gGameOverTimer;

//One Point Demo
extern "C" uint32_t sPrevFrameCs1100;
extern "C" CutsceneCameraPoint D_8012013C[14];
extern "C" CutsceneCameraPoint D_8012021C[14];
extern "C" CutsceneCameraPoint D_801204D4[14];
extern "C" CutsceneCameraPoint D_801205B4[14];
extern "C" OnePointCsFull D_801208EC[3];
extern "C" OnePointCsFull D_80120964[2];
extern "C" OnePointCsFull D_801209B4[4];
extern "C" OnePointCsFull D_80120ACC[5];
extern "C" OnePointCsFull D_80120B94[11];
extern "C" OnePointCsFull D_80120D4C[7];
extern "C" OnePointCsFull D_80120FA4[6];
extern "C" OnePointCsFull D_80121184[2];
extern "C" OnePointCsFull D_801211D4[2];
extern "C" OnePointCsFull D_8012133C[3];
extern "C" OnePointCsFull D_801213B4[5];
extern "C" OnePointCsFull D_8012151C[2];
extern "C" OnePointCsFull D_8012156C[2];
extern "C" OnePointCsFull D_801215BC[1];
extern "C" OnePointCsFull D_80121C24[7];
extern "C" OnePointCsFull D_80121D3C[3];
extern "C" OnePointCsFull D_80121F1C[4];
extern "C" OnePointCsFull D_80121FBC[4];
extern "C" OnePointCsFull D_801220D4[5];
extern "C" OnePointCsFull D_80122714[4];
extern "C" OnePointCsFull D_80122CB4[2];
extern "C" OnePointCsFull D_80122D04[2];
extern "C" OnePointCsFull D_80122E44[2][7];
extern "C" OnePointCsFull D_8012313C[3];
extern "C" OnePointCsFull D_801231B4[4];
extern "C" OnePointCsFull D_80123254[2];
extern "C" OnePointCsFull D_801232A4[1];
extern "C" OnePointCsFull D_80123894[3];
extern "C" OnePointCsFull D_8012390C[2];
extern "C" OnePointCsFull D_8012395C[3];
extern "C" OnePointCsFull D_801239D4[3];

extern "C" uint16_t gTimeIncrement;

extern "C" s16 sPlayerInitialPosX;
extern "C" s16 sPlayerInitialPosZ;
extern "C" s16 sPlayerInitialDirection;

// code_800EC960
// Related to ocarina
extern "C" u8 sOcarinaInpEnabled;
extern "C" s8 D_80130F10;
extern "C" u8 sCurOcarinaBtnVal;
extern "C" u8 sPrevOcarinaNoteVal;
extern "C" u8 sCurOcarinaBtnIdx;
extern "C" u8 sLearnSongLastBtn;
extern "C" f32 D_80130F24;
extern "C" f32 D_80130F28;
extern "C" s8 D_80130F2C;
extern "C" s8 D_80130F30;
extern "C" s8 D_80130F34;
extern "C" u8 sPlaybackState;
extern "C" u32 D_80130F3C;
extern "C" u32 sNotePlaybackTimer;
extern "C" u16 sPlaybackNotePos;
extern "C" u16 sStaffPlaybackPos;

//IDK what this is but it looks important 
extern "C" u32 sCurOcarinaBtnPress;
extern "C" u32 D_8016BA10;
extern "C" u32 sPrevOcarinaBtnPress;
extern "C" s32 D_8016BA18;
extern "C" s32 D_8016BA1C;
extern "C" u8 sCurOcarinaSong[8];
extern "C" u8 sOcarinaSongAppendPos;
extern "C" u8 sOcarinaHasStartedSong;
extern "C" u8 sOcarinaSongNoteStartIdx;
extern "C" u8 sOcarinaSongCnt;
extern "C" u16 sOcarinaAvailSongs;
extern "C" u8 sStaffPlayingPos;
extern "C" u16 sLearnSongPos[0x10];
extern "C" u16 D_8016BA50[0x10];
extern "C" u16 D_8016BA70[0x10];
extern "C" u8 sLearnSongExpectedNote[0x10];
extern "C" OcarinaNote D_8016BAA0;
extern "C" u8 sAudioHasMalonBgm;
extern "C" f32 sAudioMalonBgmDist;
extern "C" u8 sDisplayedNoteValue;



// z_message_PAL
extern "C" s16 sOcarinaNoteBufPos;
extern "C" s16 sOcarinaNoteBufLen;
extern "C" u8 sOcarinaNoteBuf[12];

extern "C" u8 D_8014B2F4;
extern "C" u8 sTextboxSkipped;
extern "C" u16 sNextTextId;
extern "C" s16 sLastPlayedSong;
extern "C" s16 sHasSunsSong;
extern "C" s16 sMessageHasSetSfx;
extern "C" u16 sOcarinaSongBitFlags;