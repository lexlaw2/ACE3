
#define ALL_BODY_PARTS ["head", "body", "leftarm", "rightarm", "leftleg", "rightleg"]

#define MEDICAL_ACTION_DISTANCE 1.75

// scale received pain to 0-2 level to select type of scream
// below 0.25: 0, from 0.25 to 0.5: 1, more than 0.5: 2
#define PAIN_TO_SCREAM(pain) (floor (4 * pain) min 2)

// scale received pain to 0-2 level to select type of scream
// below 0.33: 0, from 0.34 to 0.66: 1, more than 0.67: 2
#define PAIN_TO_MOAN(pain) (floor (3 * pain) min 2)

#define GET_NUMBER(config,default) (if (isNumber (config)) then {getNumber (config)} else {default})
#define GET_STRING(config,default) (if (isText (config)) then {getText (config)} else {default})
#define GET_ARRAY(config,default) (if (isArray (config)) then {getArray (config)} else {default})

#define DEFAULT_HEART_RATE 80

// --- blood
// 0.077 l/kg * 80kg = 6.16l
#define DEFAULT_BLOOD_VOLUME 6.0 // in liters

#define BLOOD_VOLUME_CLASS_1_HEMORRHAGE 6.000 // lost less than 15% blood, Class I Hemorrhage
#define BLOOD_VOLUME_CLASS_2_HEMORRHAGE 5.100 // lost more than 15% blood, Class II Hemorrhage
#define BLOOD_VOLUME_CLASS_3_HEMORRHAGE 4.200 // lost more than 30% blood, Class III Hemorrhage
#define BLOOD_VOLUME_CLASS_4_HEMORRHAGE 3.600 // lost more than 40% blood, Class IV Hemorrhage

// IV Change per second calculation:
// 250 ml should take 60 seconds to fill. 250 ml / 60 s ~ 4.1667 ml/s.
#define IV_CHANGE_PER_SECOND 4.1667 // in milliliters per second

// Minimum amount of damage required for penetrating wounds (also minDamage for velocity wounds)
#define PENETRATION_THRESHOLD 0.35

// To be replaced by a proper blood pressure calculation
#define BLOOD_LOSS_KNOCK_OUT_THRESHOLD 0.5 // 50% of cardiac output

// --- pain
#define PAIN_UNCONSCIOUS 0.5

// Pain fade out time (time it takes until pain is guaranteed to be completly gone)
#define PAIN_FADE_TIME 900

// Only relevant when advanced medication is disabled
// Morphine pain suppression fade out time (time it takes until pain suppression is guaranteed to be completly gone)
#define PAIN_SUPPRESSION_FADE_TIME 1800

// Chance to wake up when vitals are stable (checked once every SPONTANEOUS_WAKE_UP_INTERVAL seconds)
#define SPONTANEOUS_WAKE_UP_INTERVAL 15

#define LETHAL_HEAD_DAMAGE_THRESHOLD 1.0

// Minimum leg damage required for limping
#define LIMPING_DAMAGE_THRESHOLD 0.30

// Minimum body part damage required for blood effect on uniform
#define VISUAL_BODY_DAMAGE_THRESHOLD 0.35



// - Unit Variables ----------------------------------------------------
// These variables get stored in object space and used across components
// Defined here for easy consistency with GETVAR/SETVAR (also a list for reference)
#define VAR_BLOOD_PRESS QEGVAR(medical,bloodPressure)
#define VAR_BLOOD_VOL   QEGVAR(medical,bloodVolume)
#define VAR_CRDC_ARRST  QEGVAR(medical,inCardiacArrest)
#define VAR_HEART_RATE  QEGVAR(medical,heartRate)
#define VAR_PAIN        QEGVAR(medical,pain)
#define VAR_PAIN_SUPP   QEGVAR(medical,painSuppress)
#define VAR_UNCON       "ACE_isUnconscious"
// These variables track gradual adjustments (from medication, etc.)
#define VAR_HEART_RATE_ADJ  QEGVAR(medical,heartRateAdjustments)
#define VAR_PAIN_SUPP_ADJ   QEGVAR(medical,painSuppressAdjustments)
// These variables track the current state of status values
#define VAR_IN_PAIN     QEGVAR(medical,inPain)
#define VAR_IS_BLEEDING QEGVAR(medical,isBleeding)


// - Unit Functions ---------------------------------------------------
// Retrieval macros for common unit values
// Defined for easy consistency and speed
#define GET_BLOOD_VOLUME(unit)      (GETVAR(unit,VAR_BLOOD_VOL,DEFAULT_BLOOD_VOLUME))
#define GET_HEART_RATE(unit)        (GETVAR(unit,VAR_HEART_RATE,DEFAULT_HEART_RATE))
#define GET_PAIN(unit)              (GETVAR(unit,VAR_PAIN,0))
#define GET_PAIN_SUPPRESS(unit)     (GETVAR(unit,VAR_PAIN_SUPP,0))
#define IN_CRDC_ARRST(unit)         (GETVAR(unit,VAR_CRDC_ARRST,false))
#define IS_BLEEDING(unit)           (GETVAR(unit,VAR_IS_BLEEDING,false))
#define IS_IN_PAIN(unit)            (GETVAR(unit,VAR_HAS_PAIN,false))
#define IS_UNCONSCIOUS(unit)        (GETVAR(unit,VAR_UNCON,false))

// The following function calls are defined here just for consistency
#define GET_BLOOD_LOSS(unit)        ([unit] call EFUNC(medical_status,getBloodLoss))
#define GET_BLOOD_PRESSURE(unit)    ([unit] call EFUNC(medical_status,getBloodPressure))

// Derivative unit values commonly used
#define GET_PAIN_PERCEIVED(unit)    (0 max (GET_PAIN(unit) - GET_PAIN_SUPPRESS(unit)) min 1)
