#ifndef Z_EN_RR_H
#define Z_EN_RR_H

#include <libultraship/libultra.h>
#include "global.h"

struct EnRr;

typedef void (*EnRrActionFunc)(struct EnRr*, PlayState*);

typedef enum {
    RR_BASE_STEAL, // 0
    RR_BASE_DRAIN  // 1
} EnRrBaseType;

typedef enum {
    RR_DRAIN_RUPEE, // 0
    RR_DRAIN_LIFE,  // 1
    RR_DRAIN_MAGIC  // 2
} EnRrDrainSubtype;

typedef enum {
    RR_SIZE_NORMAL, // 0
    RR_SIZE_SMALL,  // 1
    RR_SIZE_GIANT   // 2
} EnRrSize;

typedef enum {
    RR_ORIENT_FLOOR, // 0
    RR_ORIENT_CEIL   // 1
} EnRrOrientation;

typedef enum {
    RR_MOVE_ROAMING, // 0
    RR_MOVE_STAT     // 1
} EnRrMovement;

typedef enum LikeLikeBodyPart {
    /*  0 */ LIKE_LIKE_BODYPART_0,
    /*  1 */ LIKE_LIKE_BODYPART_1,
    /*  2 */ LIKE_LIKE_BODYPART_2,
    /*  3 */ LIKE_LIKE_BODYPART_3,
    /*  4 */ LIKE_LIKE_BODYPART_4,
    /*  5 */ LIKE_LIKE_BODYPART_5,
    /*  6 */ LIKE_LIKE_BODYPART_6,
    /*  7 */ LIKE_LIKE_BODYPART_7,
    /*  8 */ LIKE_LIKE_BODYPART_8,
    /*  9 */ LIKE_LIKE_BODYPART_9,
    /* 10 */ LIKE_LIKE_BODYPART_10,
    /* 11 */ LIKE_LIKE_BODYPART_11,
    /* 12 */ LIKE_LIKE_BODYPART_12,
    /* 13 */ LIKE_LIKE_BODYPART_13,
    /* 14 */ LIKE_LIKE_BODYPART_14,
    /* 15 */ LIKE_LIKE_BODYPART_15,
    /* 16 */ LIKE_LIKE_BODYPART_16,
    /* 17 */ LIKE_LIKE_BODYPART_17,
    /* 18 */ LIKE_LIKE_BODYPART_18,
    /* 19 */ LIKE_LIKE_BODYPART_19,
    /* 20 */ LIKE_LIKE_BODYPART_MAX
} LikeLikeBodyPart;

typedef struct {
    Vec3f pos;
    Vec2f tex;
    Color_RGBA8 color;
} EnRrVertex;

typedef struct {
    /* 0x00 */ f32 height;
    /* 0x04 */ f32 heightTarget;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 scaleTarget;
    /* 0x10 */ f32 scaleMod;
               f32 ySquishMod;
    /* 0x14 */ s16 rotTargetX;
    /* 0x16 */ s16 rotTargetY;
    /* 0x18 */ s16 rotTargetZ;
    /* 0x1A */ Vec3s rot;
} EnRrStruct; // size = 0x20

typedef struct EnRr {
    Actor actor;
    EnRrActionFunc actionFunc;
    ColliderCylinder collider1;
    ColliderCylinder collider2;
    ColliderCylinder cylinder; // Used mainly for scene collision.
    ColliderJntSph bodySph;
    ColliderJntSphElement bodySphItems[4];
    s16 frameCount;
    u8 maximumHealth;
    s8 pitchScale;
    f32 reachHeight;
    s16 reachAngle;
    bool reachUp;        // Returns true if the player is in a certain range above this actor.
    u8 reachState;
    bool vacuumCooldown;
    bool tryScoop;
    u8 grabState;        // Like reachState, moves through grabStates with unique functionality.
    bool storedPlayerIsFacing; // Determines player-to-Like Like facing direction at SetupGrab for use in ThrowPlayer.
    u8 throwStrength;    // Increases throw strength depending on length of grab.
    bool stealTrigger;   // Determines if steal/drain types can start draining.
    u8 damageRelease;  // True if damage while grabbing player. Forces throw and then damage function after.
    u8 eatenSword;
    u8 eatenShield;
    u8 eatenTunic;
    u8 eatenBoots;
    u8 eatenItem;
    u8 eatenBottle;
    s8 msgEaten;    
    u8 heldItem;         // Used to determine health boost at end of retreat.
    s16 phaseRupeeTimer;
    u16 eatenRupees;
    u8 stolenLife;
    u16 slimeCounter; 
    bool slimePlayer;    // Tacks on a speed debuff and makes player slippery. 
    bool retreat;
    u8 phaseCycleCount;
    f32 scrollControl;   // Dynamically controls texture scroll speed based on segPhaseVel.
    u8 soundTimer;       // Governs time between each grab sound trigger based on current segPhaseVel value.
    u8 soundEatCounter;  // Used for throwStrength and slimeCounter.
    u8 struggleSound;
    s16 struggleCounter; // Actor-specific counter correlating to player->av2.actionvar2. Determines breakfree.
    u8 struggleSpeedup;  // When 0, struggleCounter decreases rapidly.
    u8 catchPenalty;     // Sets struggleSpeedup to 0 while this is not 0.
    u8 grabEject;        // Increases during grabPlayer if player is not within a certain range. Throws player early.
    u8 invincibilityTimer;
    u8 stunTimer;
    u8 regrabTimer;      // Strictly governs if player can be grabbed again, regardless of ocflags1.
    u8 ocPlayerTimer;    // When 0, resets OC_TYPE_PLAYER flag. 
    u8 fallTimer;        // Used by inverted Like Likes, increments when not touching a ceiling.
    u8 effectTimer;
    s16 segMovePhase;
    u16 segPhaseVel;
    u16 segPhaseVelTarget;
    f32 segWobblePhaseDiffX;
    f32 segWobbleXTarget;
    f32 segWobblePhaseDiffZ;
    f32 segWobbleZTarget;
    f32 pulseSize;
    f32 pulseSizeTarget;
    f32 wobbleSize;
    f32 wobbleSizeTarget;
    f32 segScaleModY;    // Handles body "springiness".
    f32 segScaleModYTarget;
    f32 segMoveRate;
    f32 shrinkRate;
    f32 swallowOffset;
    u8 massRef;
    s16 bodyRadiusRef;
    s16 heightRef;
    s16 mouthRadiusRef;
    f32 transitionRate;  // Rate in frames how quickly body motion changes between actions.
    f32 heightRate;
    f32 scaleRate1;
    f32 scaleRate2;      // Determines scale rate for mouth segment.
    u16 rotXRate;
    u16 rotZRate;
    u16 segPhaseVelRate;
    f32 segWobbleXRate;
    f32 segWobbleZRate;
    f32 pulseSizeRate;
    f32 wobbleSizeRate;
    u8 drawDmgEffType;
    f32 drawDmgEffAlpha;
    f32 drawDmgEffScale;
    f32 drawDmgEffFrozenSteamScale;
    Vec3f mouthPartPos;
    Vec3f bodySphPos[4];
    Vec3f bodyPartsPos[LIKE_LIKE_BODYPART_MAX];
    Vec3f effectPos[5];
    EnRrStruct bodySegs[5];
    u8 bodySegCount;
} EnRr; // size = 0x444

#endif