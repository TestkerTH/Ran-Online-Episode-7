#include "pch.h"
#include "./GLItemDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

EMGRINDING_RS_INDEX GrindRsClassToIndex ( const EMGRINDING_RS_FLAGS emClass )
{
	switch (emClass)
	{
	case EMGRINDING_RS_FIRE:	return EMGRINDING_RS_FIRE_INDEX;
	case EMGRINDING_RS_ICE:		return EMGRINDING_RS_ICE_INDEX;
	case EMGRINDING_RS_ELECTRIC:return EMGRINDING_RS_ELECTRIC_INDEX;
	case EMGRINDING_RS_POISON:	return EMGRINDING_RS_POISON_INDEX;
	case EMGRINDING_RS_SPIRIT:	return EMGRINDING_RS_SPIRIT_INDEX;
	};

	GASSERT(0&&"Invalid resistance item class.");
	return EMGRINDING_RS_FIRE_INDEX;
}

EMGRINDING_RS_FLAGS GrindIndexToRsClass ( const EMGRINDING_RS_INDEX emIndex )
{
	switch (emIndex)
	{
	case EMGRINDING_RS_FIRE_INDEX:		return EMGRINDING_RS_FIRE;
	case EMGRINDING_RS_ICE_INDEX:		return EMGRINDING_RS_ICE;
	case EMGRINDING_RS_ELECTRIC_INDEX:	return EMGRINDING_RS_ELECTRIC;
	case EMGRINDING_RS_POISON_INDEX:	return EMGRINDING_RS_POISON;
	case EMGRINDING_RS_SPIRIT_INDEX:	return EMGRINDING_RS_SPIRIT;
	};

	GASSERT(0&&"Invalid resistance item class.");
	return EMGRINDING_RS_FIRE;
}

namespace COMMENT
{
	/*
	std::string ITEMLEVEL[LEVEL_NSIZE] =
	{
		"ÀÏ¹Ý",
		"Áø±ÍÇÑ",
		"À¯ÀÏÇÑ",
		"¹«ÇÑ",
		"¹é¿­",
	};
	*/
	
	std::string ITEMLEVEL[LEVEL_NSIZE] =
	{
		"common",
		"Precious",
		"only",
		"infinite",
		"incandescence",
	};
	
	/*
	std::string ITEMTYPE[ITEM_NSIZE] =
	{
		"Âø¿ë,¹«±â,µµ±¸",
		"È­»ì",
		"¾àÇ°",
		"½ºÅ³¼­",
		"±ÍÈ¯¼­",
		"ÀÎÁõ¼­",
		"¿¬¸¶Á¦",
		"ºÎÀû",
		"½ÂÂ÷±Ç",
		"½ºÅ³Æ÷ÀÎÆ® ¸®¼Â",
		"½ºÅÝÆ÷ÀÎÆ® ¸®¼Â",
		"½ºÅ³, ½ºÅÝ ¸®¼Â",
		"¼±¹°»óÀÚ",
		"¸Á°¢ÀÇ ¼¼Á¦",
		"È®¼º±â",
		"ÆøÁ×",
		"Ä³¸¯ÅÍ Ãß°¡ Ä«µå",
		"ÀÎº¥ È®Àå Ä«µå",
		"Ã¢°í È®Àå Ä«µå",
		"Ã¢°í ¿¬°á Ä«µå",
		"ÇÁ¸®¹Ì¾ö ¼¼Æ®",
		"°³ÀÎ»óÁ¡ Çã°¡±Ç",
		"·£´ý ¾ÆÀÌÅÆ",
		"ÄÚ½ºÅù ºÐ¸®",
		"Çì¾î½ºÅ¸ÀÏ º¯°æ",
		"¾ó±¼ º¯°æ",
		"? ¾ÆÀÌÅÛ",
		"CD",
		"Ä£±¸¿¡°Ô",
		"Å¬·´È£Ãâ",
		"Çì¾î˜?ÀÌ¿ë±Ç",
		"ÀÌ¸§º¯°æ Ä«µå",
		"Çì¾î½ºÅ¸ÀÏ",
		"Çì¾îÄÃ·¯",
		"±ÍÈ¥ÁÖ",
		"Æê Ä«µå",	// PetData
		"Æê ¸ÔÀÌ",
		"Æê ÀÌ¸§º¯°æ",
		"Æê ÄÃ·¯º¯°æ",
		"Æê ½ºÅ¸ÀÏº¯°æ"
		"¾ÆÀÌÅÛ È¹µæÄ«µå"
	};
	*/
	
	std::string ITEMTYPE[ITEM_NSIZE] =
	{
		"wear, weapon, tool",
		"arrow",
		"medicine",
		"Skillbook",
		"Return letter",
		"certification",
		"abrasive",
		"charm",
		"ticket",
		"Skill Point Reset",
		"Reset stat points",
		"Skill, stat reset",
		"Gift Box",
		"Detergent of Oblivion",
		"loud speaker",
		"Firecracker",
		"Character Addition Card",
		"Inven Expansion Card",
		"Warehouse Expansion Card",
		"warehouse connection card",
		"Premium Set",
		"Individual Shop Permit",
		"Random item",
		"Separation of Kostum",
		"change hairstyle",
		"change face",
		"? item",
		"CD",
		"To friend",
		"Club call",
		"Hair?Voucher",
		"Name change card",
		"hair style",
		"Hair Color",
		"Return Lord",
		"Pet Card", // PetData
		"pet food",
		"Change pet name",
		"Change pet color",
		"Change pet style"
		"Item Acquisition Card"
	};
	
	/*
	std::string ITEMSUIT[SUIT_NSIZE] =
	{
		"¸ðÀÚ·ù",
		"»óÀÇ",
		"ÇÏÀÇ",
		"Àå°©·ù",
		"½Å¹ß·ù",

		"¹«±â·ù",

		"¸ñ°ÉÀÌ",
		"ÆÈÂî",

		"¹ÝÁö",

		"Æê A",	// PetData
		"Æê B"
		"S.R.C",
		"S.R.C Skin",
		"S.R.C Parts_A",
		"S.R.C Parts_B",
		"S.R.C Parts_C",

	};
	*/
	std::string ITEMSUIT[SUIT_NSIZE] =
	{
		"Headwear",
		"Top",
		"Pants",
		"Gloves",
		"Footwear",
		"Weaponry",
		"Necklace",
		"Bracelet",
		"Ring",
		"Pet A", // PetData
		"Pet B"
		"S.R.C",
		"S.R.C Skin",
		"S.R.C Parts_A",
		"S.R.C Parts_B",
		"S.R.C Parts_C",
		"Wings",
	};
	
	/*
	std::string ITEMDRUG[ITEM_DRUG_SIZE] =
	{
		"NUNE",
		"Ã¼·ÂÈ¸º¹",
		"±â·ÂÈ¸º¹",
		"±Ù·ÂÈ¸º¹",
		"Ã¼·Â+±â·Â È¸º¹",
		"Ã¼·Â+È°·Â È¸º¹",
		"Ã¼·Â+±â·Â+È°·Â È¸º¹",
		"ÀÌ»óÄ¡·á",

		"ÇÐ±³±ÍÈ¯",
		"½ÃÀÛ±ÍÈ¯",
		"Á÷Àü±ÍÈ¯",

		"ºÎÈ°±â´É",
		"Ã¼·ÂÈ¸º¹+ÀÌ»óÄ¡·á",
		"Ã¼·Â+±â·Â+È°·ÂÈ¸º¹+ÀÌ»óÄ¡·á"
	};
	*/
	
	std::string ITEMDRUG[ITEM_DRUG_SIZE] =
	{
		"NUNE",
		"restoration",
		"recovery",
		"muscle recovery",
		"Health + energy recovery",
		"Health + vitality recovery",
		"Physical strength + energy + vitality recovery",
		"Abnormal Treatment",

		"Back to School",
		"start return",
		"Just Return",

		"resurrection function",
		"Physical recovery + abnormal treatment",
		"Physical strength + vitality + vitality recovery + abnormal treatment"
	};

	//std::string ITEMSLOT[SLOT_NSIZE_S] =
	//{
	//	"¸ðÀÚ·ù",
	//	"»óÃ¼",
	//	"ÇÏÃ¼",
	//	"¼Õ",
	//	"¹ß",

	//	"¿À¸¥¼Õ µµ±¸",
	//	"¿À¸¥¼Õ µµ±¸ º¸Á¶",
	//	"¿Þ¼Õ µµ±¸",
	//	"¿Þ¼Õ µµ±¸ º¸Á¶",

	//	"¸ñ°ÉÀÌ",
	//	"¼Õ¸ñ",

	//	"¿À¸¥¼Õ ¼Õ°¡¶ô",
	//	"¿Þ¼Õ ¼Õ°¡¶ô"
	//};

	std::string ITEMATTACK[ITEMATT_NSIZE+1] =
	{
		"'ºñ'Âø¿ë",		//	0

		"°Ë",			//	1
		"µµ",			//	2
		"°Ë/µµ",		//	3
		"´Ü°Ë",			//	4
		"Ã¢",			//	5
		"¸ùµÕÀÌ",		//	6
		"±Ç",			//	7
		"È°",			//	8
		"ÅõÃ´",			//	9
		"Å¸ÀÔ°Ë»ç¾ÈÇÔ",	//	10
	};
	
	/*
	std::string ITEMADDON[EMADD_SIZE] =
	{
		"¾øÀ½",
		"¸íÁßÀ²",
		"È¸ÇÇÀ²",
	
		"´ë¹ÌÁö",
		"¹æ¾î·Â",

		"Ã¤·Â",
		"¸¶³ª",
		"½ºÅ×¹Ì³ª",

		"STATS Èû",
		"STATS Ã¤·Â",
		"STATS ±â·Â",
		"STATS ¹ÎÃ¸",
		"STATS Áö·Â",
		"STATS ±Ù·Â",

		"°ÝÅõÄ¡",
		"»ç°ÝÄ¡",
		"±â·ÂÄ¡",
	};
	*/
	
	std::string ITEMADDON[EMADD_SIZE] =
	{
		"None",
		"Hit Rate",
		"Evasion Rate",

		"Damage",
		"Defense",

		"Hit Point",
		"Mana",
		"Stamina",

		"STATS force",
		"Stats stats",
		"STATS Energy",
		"STATS Dexirity",
		"STATS Intelligence",
		"STATS Strength",

		"Meele",
		"Shooting",
		"Energy",
	};
	
	/*
	std::string ITEMVAR[EMVAR_SIZE] =
	{
		"¾øÀ½",
		"HP Áõ°¡À²",
		"MP Áõ°¡À²",
		"SP Áõ°¡À²",
		"HP+MP+SP Áõ°¡À²"
	};

	std::string ITEMVOL[EMVAR_SIZE] = // by °æ´ë
	{
		"¾øÀ½",
		"HP Áõ°¡·®",
		"MP Áõ°¡·®",
		"SP Áõ°¡·®",
		"HP+MP+SP Áõ°¡·®"
	};
	*/
	
	std::string ITEMVAR[EMVAR_SIZE] =
	{
		"None",
		"HP increase rate",
		"MP increase rate",
		"SP increase rate",
		"HP+MP+SP increase rate"
	};

	std::string ITEMVOL[EMVAR_SIZE] = // by Kyungdae
	{
		"None",
		"HP increase amount",
		"MP increase amount",
		"SP increase amount",
		"HP+MP+SP increase amount"
	};

	std::string ITEM_QUE_TYPE[QUESTION_SIZE] =
	{
		"none",
		"Speed Up",
		"Crazy",
		"Attack Up",
		"Exp Up",
		"Exp Get",
		"Lucky",
		"Bomb!!",
		"Mob Gen",

		"Speed Up Max",
		"Madness",
		"Attack Up Max",
		"Heal",
	};
	
	/*
	std::string ITEM_QUE_VAR1[QUESTION_SIZE] =
	{
		"¾øÀ½",
		"ÀÌµ¿¼Óµµ",
		"ÀÌµ¿¼Óµµ",
		"Damage",
		"°æÇèÄ¡",
		"¾øÀ½",
		"¹ß»ýÀ²",
		"Damage",
		"MID",

		"ÀÌµ¿¼Óµµ",
		"ÀÌµ¿¼Óµµ",
		"Damage",

		"hp"
	};

	std::string ITEM_QUE_VAR2[QUESTION_SIZE] =
	{
		"¾øÀ½",
		"¾øÀ½",
		"°ø°Ý¼Óµµ",
		"¾øÀ½",
		"¾øÀ½",
		"¾øÀ½",
		"¾øÀ½",
		"¾øÀ½",
		"SID",

		"¾øÀ½",
		"°ø°Ý¼Óµµ",
		"¾øÀ½",
		"¾øÀ½"
	};
	*/
	
	std::string ITEM_QUE_VAR1[QUESTION_SIZE] =
	{
		"None",
		"speed",
		"speed",
		"Damage",
		"Experience",
		"None",
		"incidence rate",
		"Damage",
		"MID",

		"speed",
		"speed",
		"Damage",

		"hp"
	};

	std::string ITEM_QUE_VAR2[QUESTION_SIZE] =
	{
		"None",
		"None",
		"attack speed",
		"None",
		"None",
		"None",
		"None",
		"None",
		"SID",

		"None",
		"attack speed",
		"None",
		"None"
	};

	float ITEMVAR_SCALE[EMVAR_SIZE] =
	{
		1.0f,
		100.0f,
		100.0f,
		100.0f,
		100.0f
	};

	bool IsITEMVAR_SCALE ( EMITEM_VAR emITEM_VAR )
	{
		return ITEMVAR_SCALE[emITEM_VAR]==100.0f;
	};

	/*
	std::string GRINDING_TYPE[EMGRINDING_NSIZE] =
	{
		"¾øÀ½",

		"°ø°Ý·Â",
		"¹æ¾î·Â",

		"ÀúÇ×(È­)",
		"ÀúÇ×(ºù)",
		"ÀúÇ×(Àü)",
		"ÀúÇ×(µ¶)",
		"ÀúÇ×(Á¤)",
	};

	std::string GRINDING_LEVEL[EMGRINDER_SIZE] =
	{
		"º¸Åë",
		"»óÀ§",
		"ÃÖ»óÀ§",
	};

	std::string GRINDING_RESIST[EMGRINDING_RS_NSIZE] =
	{
		"È­¿°",
		"¾óÀ½",
		"Àü±â",
		"µ¶",
		"±â",
	};
	*/
	
	std::string GRINDING_TYPE[EMGRINDING_NSIZE] =
	{
		"None",

		"offense power",
		"Defense",

		"Resistance (Fire)",
		"Resistance (Ice)",
		"Resistance (Electric)",
		"Resistance (Poison)",
		"Resistance (Energy)",
	};

	std::string GRINDING_LEVEL[EMGRINDER_SIZE] =
	{
		"Common",
		"Rare",
		"Uncommon",
	};

	std::string GRINDING_RESIST[EMGRINDING_RS_NSIZE] =
	{
		"Fire",
		"Ice",
		"Electric",
		"Poison",
		"Energy",
	};

	std::string ITEM_RANDOM_OPT[EMR_OPT_SIZE] =
	{
		"NULL",
		"DAMAGE(%)",
		"DEFENSE(%)",

		"HITRATE(+%)",
		"AVOIDRATE(+%)",

		"HP",
		"MP",
		"SP",

		"HP_INC",
		"MP_INC",
		"SP_INC",
		"HMS_INC",

		"GRIND_DAMAGE",
		"GRIND_DEFENSE",

		"ATTACK_RANGE",
		"DIS_SP",
		"RESIST"
	};


	DWORD	ITEMCOLOR[LEVEL_NSIZE] = 
	{
		0xffff0000,
		0xff00ff00,
		0xff0000ff,
		0xffffff00,
		0xffff00ff
	};


	/*
	std::string COOLTYPE[EMCOOL_SIZE] =
	{
		"¾ÆÀÌÅÛÅ¸ÀÔ",
		"¾ÆÀÌÅÛMID/SID"
	};
	*/
	
	std::string COOLTYPE[EMCOOL_SIZE] =
	{
		"Item Type",
		"Item MID/SID"
	};
};


