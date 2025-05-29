/*===========================================================================
 *
 * File:    Chunk3ds.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, June 22, 2001
 *
 * Defines the local ChunkInfo[] array describing the chunk IDs.  Should
 * only be included by the "file3ds.cpp" file.
 *
 *=========================================================================*/
#ifndef __CHUNK3DS_H
#define __CHUNK3DS_H

/* Ensure only included once */
#pragma once

chunk3ds_t ChunkInfo[] = {
	{
		0x0000,
		0,
		"NULL_CHUNK"
	},
	{
		0x0001,
		0,
		"Unknown chunk"
	},
	{
		0x0002,
		0,
		"M3D_VERSION"
	},
	{
		0x0005,
		0,
		"M3D_KFVERSION "
	},
	{
		0x0010,
		0,
		"COLOR_F"
	},
	{
		0x0011,
		0,
		"COLOR_24"
	},
	{
		0x0012,
		0,
		"LIN_COLOR_24"
	},
	{
		0x0013,
		0,
		"LIN_COLOR_F"
	},
	{
		0x0030,
		0,
		"INT_PERCENTAGE"
	},
	{
		0x0031,
		0,
		"FLOAT_PERCENTAGE"
	},
	{
		0x0100,
		0,
		"MASTER_SCALE"
	},
	{
		0x0995,
		0,
		"ChunkType "
	},
	{
		0x0996,
		0,
		"ChunkUnique "
	},
	{
		0x0997,
		0,
		"NotChunk "
	},
	{
		0x0998,
		0,
		"Container "
	},
	{
		0x0999,
		0,
		"IsChunk "
	},
	{
		0x0c3c,
		0,
		"C_SXP_SELFI_MASKDATA "
	},
	{
		0x1100,
		0,
		"BIT_MAP"
	},
	{
		0x1101,
		0,
		"USE_BIT_MAP "
	},
	{
		0x1200,
		0,
		"SOLID_BGND"
	},
	{
		0x1201,
		0,
		"USE_SOLID_BGND "
	},
	{
		0x1300,
		0,
		"V_GRADIENT"
	},
	{
		0x1301,
		0,
		"USE_V_GRADIENT 	"
	},
	{
		0x1400,
		0,
		"LO_SHADOW_BIAS"
	},
	{
		0x1410,
		0,
		"HI_SHADOW_BIAS 	"
	},
	{
		0x1420,
		0,
		"SHADOW_MAP_SIZE"
	},
	{
		0x1430,
		0,
		"SHADOW_SAMPLES 	"
	},
	{
		0x1440,
		0,
		"SHADOW_RANGE 	"
	},
	{
		0x1450,
		0,
		"SHADOW_FILTER"
	},
	{
		0x1460,
		0,
		"RAY_BIAS"
	},
	{
		0x1500,
		0,
		"O_CONSTS"
	},
	{
		0x2100,
		0,
		"AMBIENT_LIGHT "
	},
	{
		0x2200,
		0,
		"FOG"
	},
	{
		0x2201,
		0,
		"USE_FOG "
	},
	{
		0x2210,
		0,
		"FOG_BGND "
	},
	{
		0x2300,
		0,
		"DISTANCE_CUE"
	},
	{
		0x2301,
		0,
		"USE_DISTANCE_CUE "
	},
	{
		0x2302,
		0,
		"LAYER_FOG"
	},
	{
		0x2303,
		0,
		"USE_LAYER_FOG "
	},
	{
		0x2310,
		0,
		"DCUE_BGND "
	},
	{
		0x2d2d,
		0,
		"SMAGIC "
	},
	{
		0x2d3d,
		0,
		"LMAGIC "
	},
	{
		0x3000,
		0,
		"DEFAULT_VIEW "
	},
	{
		0x3010,
		0,
		"VIEW_TOP"
	},
	{
		0x3020,
		0,
		"VIEW_BOTTOM"
	},
	{
		0x3030,
		0,
		"VIEW_LEFT"
	},
	{
		0x3040,
		0,
		"VIEW_RIGHT"
	},
	{
		0x3050,
		0,
		"VIEW_FRONT"
	},
	{
		0x3060,
		0,
		"VIEW_BACK"
	},
	{
		0x3070,
		0,
		"VIEW_USER"
	},
	{
		0x3080,
		0,
		"VIEW_CAMERA"
	},
	{
		0x3090,
		0,
		"VIEW_WINDOW "
	},
	{
		0x3d3d,
		1,
		"Edit 3DS DATA"
	},
	{
		0x3d3e,
		0,
		"MESH_VERSION "
	},
	{
		0x3daa,
		0,
		"MLIBMAGIC"
	},
	{
		0x3dc2,
		0,
		"PRJMAGIC"
	},
	{
		0x3dff,
		0,
		"MATMAGIC"
	},
	{
		0x4000,
		0,
		"NAMED_OBJECT"
	},
	{
		0x4010,
		0,
		"OBJ_HIDDEN "
	},
	{
		0x4011,
		0,
		"OBJ_VIS_LOFTER "
	},
	{
		0x4012,
		0,
		"OBJ_DOESNT_CAST "
	},
	{
		0x4013,
		0,
		"OBJ_MATTE "
	},
	{
		0x4014,
		0,
		"OBJ_FAST "
	},
	{
		0x4015,
		0,
		"OBJ_PROCEDURAL "
	},
	{
		0x4016,
		0,
		"OBJ_FROZEN "
	},
	{
		0x4017,
		0,
		"OBJ_DONT_RCVSHADOW "
	},
	{
		0x4100,
		1,
		"N_TRI_OBJECT"
	},
	{
		0x4110,
		0,
		"POINT_ARRAY"
	},
	{
		0x4111,
		0,
		"POINT_FLAG_ARRAY"
	},
	{
		0x4120,
		0,
		"FACE_ARRAY"
	},
	{
		0x4130,
		0,
		"MSH_MAT_GROUP"
	},
	{
		0x4131,
		0,
		"OLD_MAT_GROUP "
	},
	{
		0x4140,
		0,
		"TEX_VERTS"
	},
	{
		0x4150,
		0,
		"SMOOTH_GROUP"
	},
	{
		0x4160,
		0,
		"MESH_MATRIX"
	},
	{
		0x4165,
		0,
		"MESH_COLOR"
	},
	{
		0x4170,
		0,
		"MESH_TEXTURE_INFO"
	},
	{
		0x4181,
		0,
		"PROC_NAME "
	},
	{
		0x4182,
		0,
		"PROC_DATA "
	},
	{
		0x4190,
		0,
		"MSH_BOXMAP "
	},
	{
		0x4400,
		0,
		"N_D_L_OLD "
	},
	{
		0x4500,
		0,
		"N_CAM_OLD "
	},
	{
		0x4600,
		0,
		"N_DIRECT_LIGHT"
	},
	{
		0x4610,
		0,
		"DL_SPOTLIGHT"
	},
	{
		0x4620,
		0,
		"DL_OFF "
	},
	{
		0x4625,
		0,
		"DL_ATTENUATE "
	},
	{
		0x4627,
		0,
		"DL_RAYSHAD "
	},
	{
		0x4630,
		0,
		"DL_SHADOWED "
	},
	{
		0x4640,
		0,
		"DL_LOCAL_SHADOW "
	},
	{
		0x4641,
		0,
		"DL_LOCAL_SHADOW2 "
	},
	{
		0x4650,
		0,
		"DL_SEE_CONE "
	},
	{
		0x4651,
		0,
		"DL_SPOT_RECTANGULAR "
	},
	{
		0x4652,
		0,
		"DL_SPOT_OVERSHOOT "
	},
	{
		0x4653,
		0,
		"DL_SPOT_PROJECTOR "
	},
	{
		0x4654,
		0,
		"DL_EXCLUDE "
	},
	{
		0x4655,
		0,
		"DL_RANGE "
	},
	{
		0x4656,
		0,
		"DL_SPOT_ROLL"
	},
	{
		0x4657,
		0,
		"DL_SPOT_ASPECT "
	},
	{
		0x4658,
		0,
		"DL_RAY_BIAS"
	},
	{
		0x4659,
		0,
		"DL_INNER_RANGE"
	},
	{
		0x465a,
		0,
		"DL_OUTER_RANGE"
	},
	{
		0x465b,
		0,
		"DL_MULTIPLIER"
	},
	{
		0x4680,
		0,
		"N_AMBIENT_LIGHT "
	},
	{
		0x4700,
		0,
		"N_CAMERA"
	},
	{
		0x4710,
		0,
		"CAM_SEE_CONE "
	},
	{
		0x4720,
		0,
		"CAM_RANGES"
	},
	{
		0x4d4d,
		1,
		"Main 3DS Data"
	},
	{
		0x4f00,
		0,
		"HIERARCHY "
	},
	{
		0x4f10,
		0,
		"PARENT_OBJECT "
	},
	{
		0x4f20,
		0,
		"PIVOT_OBJECT "
	},
	{
		0x4f30,
		0,
		"PIVOT_LIMITS "
	},
	{
		0x4f40,
		0,
		"PIVOT_ORDER "
	},
	{
		0x4f50,
		0,
		"XLATE_RANGE "
	},
	{
		0x5000,
		0,
		"POLY_2D "
	},
	{
		0x5010,
		0,
		"SHAPE_OK "
	},
	{
		0x5011,
		0,
		"SHAPE_NOT_OK "
	},
	{
		0x5020,
		0,
		"SHAPE_HOOK "
	},
	{
		0x6000,
		0,
		"PATH_3D "
	},
	{
		0x6005,
		0,
		"PATH_MATRIX "
	},
	{
		0x6010,
		0,
		"SHAPE_2D "
	},
	{
		0x6020,
		0,
		"M_SCALE "
	},
	{
		0x6030,
		0,
		"M_TWIST "
	},
	{
		0x6040,
		0,
		"M_TEETER "
	},
	{
		0x6050,
		0,
		"M_FIT "
	},
	{
		0x6060,
		0,
		"M_BEVEL "
	},
	{
		0x6070,
		0,
		"XZ_CURVE "
	},
	{
		0x6080,
		0,
		"YZ_CURVE "
	},
	{
		0x6090,
		0,
		"INTERPCT "
	},
	{
		0x60a0,
		0,
		"DEFORM_LIMIT "
	},
	{
		0x6100,
		0,
		"USE_CONTOUR "
	},
	{
		0x6110,
		0,
		"USE_TWEEN "
	},
	{
		0x6120,
		0,
		"USE_SCALE "
	},
	{
		0x6130,
		0,
		"USE_TWIST "
	},
	{
		0x6140,
		0,
		"USE_TEETER "
	},
	{
		0x6150,
		0,
		"USE_FIT "
	},
	{
		0x6160,
		0,
		"USE_BEVEL "
	},
	{
		0x7000,
		0,
		"VIEWPORT_LAYOUT_OLD "
	},
	{
		0x7001,
		0,
		"VIEWPORT_LAYOUT"
	},
	{
		0x7010,
		0,
		"VIEWPORT_DATA_OLD "
	},
	{
		0x7011,
		0,
		"VIEWPORT_DATA"
	},
	{
		0x7012,
		0,
		"VIEWPORT_DATA_3"
	},
	{
		0x7020,
		0,
		"VIEWPORT_SIZE"
	},
	{
		0x7030,
		0,
		"NETWORK_VIEW "
	},
	{
		0x8000,
		0,
		"XDATA_SECTION "
	},
	{
		0x8001,
		0,
		"XDATA_ENTRY "
	},
	{
		0x8002,
		0,
		"XDATA_APPNAME "
	},
	{
		0x8003,
		0,
		"XDATA_STRING "
	},
	{
		0x8004,
		0,
		"XDATA_FLOAT "
	},
	{
		0x8005,
		0,
		"XDATA_DOUBLE "
	},
	{
		0x8006,
		0,
		"XDATA_SHORT "
	},
	{
		0x8007,
		0,
		"XDATA_LONG "
	},
	{
		0x8008,
		0,
		"XDATA_VOID "
	},
	{
		0x8009,
		0,
		"XDATA_GROUP "
	},
	{
		0x800a,
		0,
		"XDATA_RFU6 "
	},
	{
		0x800b,
		0,
		"XDATA_RFU5 "
	},
	{
		0x800c,
		0,
		"XDATA_RFU4 "
	},
	{
		0x800d,
		0,
		"XDATA_RFU3 "
	},
	{
		0x800e,
		0,
		"XDATA_RFU2 "
	},
	{
		0x800f,
		0,
		"XDATA_RFU1 "
	},
	{
		0x80f0,
		0,
		"PARENT_NAME "
	},
	{
		0xa000,
		0,
		"MAT_NAME"
	},
	{
		0xa010,
		0,
		"MAT_AMBIENT"
	},
	{
		0xa020,
		0,
		"MAT_DIFFUSE"
	},
	{
		0xa030,
		0,
		"MAT_SPECULAR"
	},
	{
		0xa040,
		0,
		"MAT_SHININESS"
	},
	{
		0xa041,
		0,
		"MAT_SHIN2PCT"
	},
	{
		0xa042,
		0,
		"MAT_SHIN3PCT"
	},
	{
		0xa050,
		0,
		"MAT_TRANSPARENCY"
	},
	{
		0xa052,
		0,
		"MAT_XPFALL"
	},
	{
		0xa053,
		0,
		"MAT_REFBLUR"
	},
	{
		0xa080,
		0,
		"MAT_SELF_ILLUM "
	},
	{
		0xa081,
		0,
		"MAT_TWO_SIDE "
	},
	{
		0xa082,
		0,
		"MAT_DECAL "
	},
	{
		0xa083,
		0,
		"MAT_ADDITIVE "
	},
	{
		0xa084,
		0,
		"MAT_SELF_ILPCT"
	},
	{
		0xa085,
		0,
		"MAT_WIRE "
	},
	{
		0xa086,
		0,
		"MAT_SUPERSMP "
	},
	{
		0xa087,
		0,
		"MAT_WIRESIZE"
	},
	{
		0xa088,
		0,
		"MAT_FACEMAP "
	},
	{
		0xa08a,
		0,
		"MAT_XPFALLIN "
	},
	{
		0xa08c,
		0,
		"MAT_PHONGSOFT "
	},
	{
		0xa08e,
		0,
		"MAT_WIREABS "
	},
	{
		0xa100,
		0,
		"MAT_SHADING"
	},
	{
		0xa200,
		1,
		"MAT_TEXMAP"
	},
	{
		0xa204,
		0,
		"MAT_SPECMAP"
	},
	{
		0xa210,
		0,
		"MAT_OPACMAP"
	},
	{
		0xa220,
		0,
		"MAT_REFLMAP"
	},
	{
		0xa230,
		0,
		"MAT_BUMPMAP"
	},
	{
		0xa240,
		0,
		"MAT_USE_XPFALL "
	},
	{
		0xa250,
		0,
		"MAT_USE_REFBLUR "
	},
	{
		0xa252,
		0,
		"MAT_BUMP_PERCENT "
	},
	{
		0xa300,
		0,
		"MAT_MAPNAME"
	},
	{
		0xa310,
		0,
		"MAT_ACUBIC "
	},
	{
		0xa320,
		0,
		"MAT_SXP_TEXT_DATA "
	},
	{
		0xa321,
		0,
		"MAT_SXP_TEXT2_DATA "
	},
	{
		0xa322,
		0,
		"MAT_SXP_OPAC_DATA "
	},
	{
		0xa324,
		0,
		"MAT_SXP_BUMP_DATA "
	},
	{
		0xa325,
		0,
		"MAT_SXP_SPEC_DATA "
	},
	{
		0xa326,
		0,
		"MAT_SXP_SHIN_DATA "
	},
	{
		0xa328,
		0,
		"MAT_SXP_SELFI_DATA "
	},
	{
		0xa32a,
		0,
		"MAT_SXP_TEXT_MASKDATA "
	},
	{
		0xa32c,
		0,
		"MAT_SXP_TEXT2_MASKDATA "
	},
	{
		0xa32e,
		0,
		"MAT_SXP_OPAC_MASKDATA "
	},
	{
		0xa330,
		0,
		"MAT_SXP_BUMP_MASKDATA "
	},
	{
		0xa332,
		0,
		"MAT_SXP_SPEC_MASKDATA "
	},
	{
		0xa334,
		0,
		"MAT_SXP_SHIN_MASKDATA "
	},
	{
		0xa336,
		0,
		"MAT_SXP_SELFI_MASKDATA "
	},
	{
		0xa338,
		0,
		"MAT_SXP_REFL_MASKDATA "
	},
	{
		0xa33a,
		0,
		"MAT_TEX2MAP "
	},
	{
		0xa33c,
		0,
		"MAT_SHINMAP "
	},
	{
		0xa33d,
		0,
		"MAT_SELFIMAP "
	},
	{
		0xa33e,
		0,
		"MAT_TEXMASK "
	},
	{
		0xa340,
		0,
		"MAT_TEX2MASK "
	},
	{
		0xa342,
		0,
		"MAT_OPACMASK "
	},
	{
		0xa344,
		0,
		"MAT_BUMPMASK "
	},
	{
		0xa346,
		0,
		"MAT_SHINMASK "
	},
	{
		0xa348,
		0,
		"MAT_SPECMASK "
	},
	{
		0xa34a,
		0,
		"MAT_SELFIMASK "
	},
	{
		0xa34c,
		0,
		"MAT_REFLMASK "
	},
	{
		0xa350,
		0,
		"MAT_MAP_TILINGOLD "
	},
	{
		0xa351,
		0,
		"MAT_MAP_TILING"
	},
	{
		0xa352,
		0,
		"MAT_MAP_TEXBLUR_OLD "
	},
	{
		0xa353,
		0,
		"MAT_MAP_TEXBLUR"
	},
	{
		0xa354,
		0,
		"MAT_MAP_USCALE "
	},
	{
		0xa356,
		0,
		"MAT_MAP_VSCALE "
	},
	{
		0xa358,
		0,
		"MAT_MAP_UOFFSET "
	},
	{
		0xa35a,
		0,
		"MAT_MAP_VOFFSET "
	},
	{
		0xa35c,
		0,
		"MAT_MAP_ANG "
	},
	{
		0xa360,
		0,
		"MAT_MAP_COL1 "
	},
	{
		0xa362,
		0,
		"MAT_MAP_COL2 "
	},
	{
		0xa364,
		0,
		"MAT_MAP_RCOL "
	},
	{
		0xa366,
		0,
		"MAT_MAP_GCOL "
	},
	{
		0xa368,
		0,
		"MAT_MAP_BCOL "
	},
	{
		0xafff,
		1,
		"MAT_ENTRY "
	},
	{
		0xb000,
		1,
		"KeyFrame Data"
	},
	{
		0xb001,
		0,
		"AMBIENT_NODE_TAG "
	},
	{
		0xb002,
		1,
		"OBJECT_NODE_TAG"
	},
	{
		0xb003,
		0,
		"CAMERA_NODE_TAG"
	},
	{
		0xb004,
		0,
		"TARGET_NODE_TAG"
	},
	{
		0xb005,
		0,
		"LIGHT_NODE_TAG"
	},
	{
		0xb006,
		0,
		"L_TARGET_NODE_TAG"
	},
	{
		0xb007,
		0,
		"SPOTLIGHT_NODE_TAG"
	},
	{
		0xb008,
		0,
		"KFSEG"
	},
	{
		0xb009,
		0,
		"KFCURTIME"
	},
	{
		0xb00a,
		0,
		"KFHDR"
	},
	{
		0xb010,
		0,
		"NODE_HDR"
	},
	{
		0xb011,
		0,
		"INSTANCE_NAME "
	},
	{
		0xb012,
		0,
		"PRESCALE "
	},
	{
		0xb013,
		0,
		"PIVOT"
	},
	{
		0xb014,
		0,
		"BOUNDBOX "
	},
	{
		0xb015,
		0,
		"MORPH_SMOOTH"
	},
	{
		0xb020,
		0,
		"POS_TRACK_TAG"
	},
	{
		0xb021,
		0,
		"ROT_TRACK_TAG"
	},
	{
		0xb022,
		0,
		"SCL_TRACK_TAG"
	},
	{
		0xb023,
		0,
		"FOV_TRACK_TAG"
	},
	{
		0xb024,
		0,
		"ROLL_TRACK_TAG"
	},
	{
		0xb025,
		0,
		"COL_TRACK_TAG"
	},
	{
		0xb026,
		0,
		"MORPH_TRACK_TAG"
	},
	{
		0xb027,
		0,
		"HOT_TRACK_TAG"
	},
	{
		0xb028,
		0,
		"FALL_TRACK_TAG"
	},
	{
		0xb029,
		0,
		"HIDE_TRACK_TAG "
	},
	{
		0xb030,
		0,
		"NODE_ID"
	},
	{
		0xc010,
		0,
		"C_MDRAWER "
	},
	{
		0xc020,
		0,
		"C_TDRAWER "
	},
	{
		0xc030,
		0,
		"C_SHPDRAWER "
	},
	{
		0xc040,
		0,
		"C_MODDRAWER "
	},
	{
		0xc050,
		0,
		"C_RIPDRAWER "
	},
	{
		0xc060,
		0,
		"C_TXDRAWER "
	},
	{
		0xc062,
		0,
		"C_PDRAWER "
	},
	{
		0xc064,
		0,
		"C_MTLDRAWER "
	},
	{
		0xc066,
		0,
		"C_FLIDRAWER "
	},
	{
		0xc067,
		0,
		"C_CUBDRAWER "
	},
	{
		0xc070,
		0,
		"C_MFILE "
	},
	{
		0xc080,
		0,
		"C_SHPFILE "
	},
	{
		0xc090,
		0,
		"C_MODFILE "
	},
	{
		0xc0a0,
		0,
		"C_RIPFILE "
	},
	{
		0xc0b0,
		0,
		"C_TXFILE "
	},
	{
		0xc0b2,
		0,
		"C_PFILE "
	},
	{
		0xc0b4,
		0,
		"C_MTLFILE "
	},
	{
		0xc0b6,
		0,
		"C_FLIFILE "
	},
	{
		0xc0b8,
		0,
		"C_PALFILE "
	},
	{
		0xc0c0,
		0,
		"C_TX_STRING "
	},
	{
		0xc0d0,
		0,
		"C_CONSTS "
	},
	{
		0xc0e0,
		0,
		"C_SNAPS "
	},
	{
		0xc0f0,
		0,
		"C_GRIDS "
	},
	{
		0xc100,
		0,
		"C_ASNAPS "
	},
	{
		0xc110,
		0,
		"C_GRID_RANGE "
	},
	{
		0xc120,
		0,
		"C_RENDTYPE "
	},
	{
		0xc130,
		0,
		"C_PROGMODE "
	},
	{
		0xc140,
		0,
		"C_PREVMODE "
	},
	{
		0xc150,
		0,
		"C_MODWMODE "
	},
	{
		0xc160,
		0,
		"C_MODMODEL "
	},
	{
		0xc170,
		0,
		"C_ALL_LINES "
	},
	{
		0xc180,
		0,
		"C_BACK_TYPE "
	},
	{
		0xc190,
		0,
		"C_MD_CS "
	},
	{
		0xc1a0,
		0,
		"C_MD_CE "
	},
	{
		0xc1b0,
		0,
		"C_MD_SML "
	},
	{
		0xc1c0,
		0,
		"C_MD_SMW "
	},
	{
		0xc1c3,
		0,
		"C_LOFT_WITH_TEXTURE "
	},
	{
		0xc1c4,
		0,
		"C_LOFT_L_REPEAT "
	},
	{
		0xc1c5,
		0,
		"C_LOFT_W_REPEAT "
	},
	{
		0xc1c6,
		0,
		"C_LOFT_UV_NORMALIZE "
	},
	{
		0xc1c7,
		0,
		"C_WELD_LOFT "
	},
	{
		0xc1d0,
		0,
		"C_MD_PDET "
	},
	{
		0xc1e0,
		0,
		"C_MD_SDET "
	},
	{
		0xc1f0,
		0,
		"C_RGB_RMODE "
	},
	{
		0xc200,
		0,
		"C_RGB_HIDE "
	},
	{
		0xc202,
		0,
		"C_RGB_MAPSW "
	},
	{
		0xc204,
		0,
		"C_RGB_TWOSIDE "
	},
	{
		0xc208,
		0,
		"C_RGB_SHADOW "
	},
	{
		0xc210,
		0,
		"C_RGB_AA "
	},
	{
		0xc220,
		0,
		"C_RGB_OVW "
	},
	{
		0xc230,
		0,
		"C_RGB_OVH "
	},
	{
		0xc23d,
		0,
		"CMAGIC "
	},
	{
		0xc240,
		0,
		"C_RGB_PICTYPE "
	},
	{
		0xc250,
		0,
		"C_RGB_OUTPUT "
	},
	{
		0xc253,
		0,
		"C_RGB_TODISK "
	},
	{
		0xc254,
		0,
		"C_RGB_COMPRESS "
	},
	{
		0xc255,
		0,
		"C_JPEG_COMPRESSION "
	},
	{
		0xc256,
		0,
		"C_RGB_DISPDEV "
	},
	{
		0xc259,
		0,
		"C_RGB_HARDDEV "
	},
	{
		0xc25a,
		0,
		"C_RGB_PATH "
	},
	{
		0xc25b,
		0,
		"C_BITMAP_DRAWER "
	},
	{
		0xc260,
		0,
		"C_RGB_FILE "
	},
	{
		0xc270,
		0,
		"C_RGB_OVASPECT "
	},
	{
		0xc271,
		0,
		"C_RGB_ANIMTYPE "
	},
	{
		0xc272,
		0,
		"C_RENDER_ALL "
	},
	{
		0xc273,
		0,
		"C_REND_FROM "
	},
	{
		0xc274,
		0,
		"C_REND_TO "
	},
	{
		0xc275,
		0,
		"C_REND_NTH "
	},
	{
		0xc276,
		0,
		"C_PAL_TYPE "
	},
	{
		0xc277,
		0,
		"C_RND_TURBO "
	},
	{
		0xc278,
		0,
		"C_RND_MIP "
	},
	{
		0xc279,
		0,
		"C_BGND_METHOD "
	},
	{
		0xc27a,
		0,
		"C_AUTO_REFLECT "
	},
	{
		0xc27b,
		0,
		"C_VP_FROM "
	},
	{
		0xc27c,
		0,
		"C_VP_TO "
	},
	{
		0xc27d,
		0,
		"C_VP_NTH "
	},
	{
		0xc27e,
		0,
		"C_REND_TSTEP "
	},
	{
		0xc27f,
		0,
		"C_VP_TSTEP "
	},
	{
		0xc280,
		0,
		"C_SRDIAM "
	},
	{
		0xc290,
		0,
		"C_SRDEG "
	},
	{
		0xc2a0,
		0,
		"C_SRSEG "
	},
	{
		0xc2b0,
		0,
		"C_SRDIR "
	},
	{
		0xc2c0,
		0,
		"C_HETOP "
	},
	{
		0xc2d0,
		0,
		"C_HEBOT "
	},
	{
		0xc2e0,
		0,
		"C_HEHT "
	},
	{
		0xc2f0,
		0,
		"C_HETURNS "
	},
	{
		0xc300,
		0,
		"C_HEDEG "
	},
	{
		0xc310,
		0,
		"C_HESEG "
	},
	{
		0xc320,
		0,
		"C_HEDIR "
	},
	{
		0xc330,
		0,
		"C_QUIKSTUFF "
	},
	{
		0xc340,
		0,
		"C_SEE_LIGHTS "
	},
	{
		0xc350,
		0,
		"C_SEE_CAMERAS "
	},
	{
		0xc360,
		0,
		"C_SEE_3D "
	},
	{
		0xc370,
		0,
		"C_MESHSEL "
	},
	{
		0xc380,
		0,
		"C_MESHUNSEL "
	},
	{
		0xc390,
		0,
		"C_POLYSEL "
	},
	{
		0xc3a0,
		0,
		"C_POLYUNSEL "
	},
	{
		0xc3a2,
		0,
		"C_SHPLOCAL "
	},
	{
		0xc3a4,
		0,
		"C_MSHLOCAL "
	},
	{
		0xc3b0,
		0,
		"C_NUM_FORMAT "
	},
	{
		0xc3c0,
		0,
		"C_ARCH_DENOM "
	},
	{
		0xc3d0,
		0,
		"C_IN_DEVICE "
	},
	{
		0xc3e0,
		0,
		"C_MSCALE "
	},
	{
		0xc3f0,
		0,
		"C_COMM_PORT "
	},
	{
		0xc400,
		0,
		"C_TAB_BASES "
	},
	{
		0xc410,
		0,
		"C_TAB_DIVS "
	},
	{
		0xc420,
		0,
		"C_MASTER_SCALES "
	},
	{
		0xc430,
		0,
		"C_SHOW_1STVERT "
	},
	{
		0xc440,
		0,
		"C_SHAPER_OK "
	},
	{
		0xc450,
		0,
		"C_LOFTER_OK "
	},
	{
		0xc460,
		0,
		"C_EDITOR_OK "
	},
	{
		0xc470,
		0,
		"C_KEYFRAMER_OK "
	},
	{
		0xc480,
		0,
		"C_PICKSIZE "
	},
	{
		0xc490,
		0,
		"C_MAPTYPE "
	},
	{
		0xc4a0,
		0,
		"C_MAP_DISPLAY "
	},
	{
		0xc4b0,
		0,
		"C_TILE_XY "
	},
	{
		0xc4c0,
		0,
		"C_MAP_XYZ "
	},
	{
		0xc4d0,
		0,
		"C_MAP_SCALE "
	},
	{
		0xc4e0,
		0,
		"C_MAP_MATRIX_OLD "
	},
	{
		0xc4e1,
		0,
		"C_MAP_MATRIX "
	},
	{
		0xc4f0,
		0,
		"C_MAP_WID_HT "
	},
	{
		0xc500,
		0,
		"C_OBNAME "
	},
	{
		0xc510,
		0,
		"C_CAMNAME "
	},
	{
		0xc520,
		0,
		"C_LTNAME "
	},
	{
		0xc525,
		0,
		"C_CUR_MNAME "
	},
	{
		0xc526,
		0,
		"C_CURMTL_FROM_MESH "
	},
	{
		0xc527,
		0,
		"C_GET_SHAPE_MAKE_FACES "
	},
	{
		0xc530,
		0,
		"C_DETAIL "
	},
	{
		0xc540,
		0,
		"C_VERTMARK "
	},
	{
		0xc550,
		0,
		"C_MSHAX "
	},
	{
		0xc560,
		0,
		"C_MSHCP "
	},
	{
		0xc570,
		0,
		"C_USERAX "
	},
	{
		0xc580,
		0,
		"C_SHOOK "
	},
	{
		0xc590,
		0,
		"C_RAX "
	},
	{
		0xc5a0,
		0,
		"C_STAPE "
	},
	{
		0xc5b0,
		0,
		"C_LTAPE "
	},
	{
		0xc5c0,
		0,
		"C_ETAPE "
	},
	{
		0xc5c8,
		0,
		"C_KTAPE "
	},
	{
		0xc5d0,
		0,
		"C_SPHSEGS "
	},
	{
		0xc5e0,
		0,
		"C_GEOSMOOTH "
	},
	{
		0xc5f0,
		0,
		"C_HEMISEGS "
	},
	{
		0xc600,
		0,
		"C_PRISMSEGS "
	},
	{
		0xc610,
		0,
		"C_PRISMSIDES "
	},
	{
		0xc620,
		0,
		"C_TUBESEGS "
	},
	{
		0xc630,
		0,
		"C_TUBESIDES "
	},
	{
		0xc640,
		0,
		"C_TORSEGS "
	},
	{
		0xc650,
		0,
		"C_TORSIDES "
	},
	{
		0xc660,
		0,
		"C_CONESIDES "
	},
	{
		0xc661,
		0,
		"C_CONESEGS "
	},
	{
		0xc670,
		0,
		"C_NGPARMS "
	},
	{
		0xc680,
		0,
		"C_PTHLEVEL "
	},
	{
		0xc690,
		0,
		"C_MSCSYM "
	},
	{
		0xc6a0,
		0,
		"C_MFTSYM "
	},
	{
		0xc6b0,
		0,
		"C_MTTSYM "
	},
	{
		0xc6c0,
		0,
		"C_SMOOTHING "
	},
	{
		0xc6d0,
		0,
		"C_MODICOUNT "
	},
	{
		0xc6e0,
		0,
		"C_FONTSEL "
	},
	{
		0xc6f0,
		0,
		"C_TESS_TYPE "
	},
	{
		0xc6f1,
		0,
		"C_TESS_TENSION "
	},
	{
		0xc700,
		0,
		"C_SEG_START "
	},
	{
		0xc705,
		0,
		"C_SEG_END "
	},
	{
		0xc710,
		0,
		"C_CURTIME "
	},
	{
		0xc715,
		0,
		"C_ANIMLENGTH "
	},
	{
		0xc720,
		0,
		"C_PV_FROM "
	},
	{
		0xc725,
		0,
		"C_PV_TO "
	},
	{
		0xc730,
		0,
		"C_PV_DOFNUM "
	},
	{
		0xc735,
		0,
		"C_PV_RNG "
	},
	{
		0xc740,
		0,
		"C_PV_NTH "
	},
	{
		0xc745,
		0,
		"C_PV_TYPE "
	},
	{
		0xc750,
		0,
		"C_PV_METHOD "
	},
	{
		0xc755,
		0,
		"C_PV_FPS "
	},
	{
		0xc765,
		0,
		"C_VTR_FRAMES "
	},
	{
		0xc770,
		0,
		"C_VTR_HDTL "
	},
	{
		0xc771,
		0,
		"C_VTR_HD "
	},
	{
		0xc772,
		0,
		"C_VTR_TL "
	},
	{
		0xc775,
		0,
		"C_VTR_IN "
	},
	{
		0xc780,
		0,
		"C_VTR_PK "
	},
	{
		0xc785,
		0,
		"C_VTR_SH "
	},
	{
		0xc790,
		0,
		"C_WORK_MTLS "
	},
	{
		0xc792,
		0,
		"C_WORK_MTLS_2 "
	},
	{
		0xc793,
		0,
		"C_WORK_MTLS_3 "
	},
	{
		0xc794,
		0,
		"C_WORK_MTLS_4 "
	},
	{
		0xc7a1,
		0,
		"C_BGTYPE "
	},
	{
		0xc7b0,
		0,
		"C_MEDTILE "
	},
	{
		0xc7d0,
		0,
		"C_LO_CONTRAST "
	},
	{
		0xc7d1,
		0,
		"C_HI_CONTRAST "
	},
	{
		0xc7e0,
		0,
		"C_FROZ_DISPLAY "
	},
	{
		0xc7f0,
		0,
		"C_BOOLWELD "
	},
	{
		0xc7f1,
		0,
		"C_BOOLTYPE "
	},
	{
		0xc900,
		0,
		"C_ANG_THRESH "
	},
	{
		0xc901,
		0,
		"C_SS_THRESH "
	},
	{
		0xc903,
		0,
		"C_TEXTURE_BLUR_DEFAULT "
	},
	{
		0xca00,
		0,
		"C_MAPDRAWER "
	},
	{
		0xca01,
		0,
		"C_MAPDRAWER1 "
	},
	{
		0xca02,
		0,
		"C_MAPDRAWER2 "
	},
	{
		0xca03,
		0,
		"C_MAPDRAWER3 "
	},
	{
		0xca04,
		0,
		"C_MAPDRAWER4 "
	},
	{
		0xca05,
		0,
		"C_MAPDRAWER5 "
	},
	{
		0xca06,
		0,
		"C_MAPDRAWER6 "
	},
	{
		0xca07,
		0,
		"C_MAPDRAWER7 "
	},
	{
		0xca08,
		0,
		"C_MAPDRAWER8 "
	},
	{
		0xca09,
		0,
		"C_MAPDRAWER9 "
	},
	{
		0xca10,
		0,
		"C_MAPDRAWER_ENTRY "
	},
	{
		0xca20,
		0,
		"C_BACKUP_FILE "
	},
	{
		0xca21,
		0,
		"C_DITHER_256 "
	},
	{
		0xca22,
		0,
		"C_SAVE_LAST "
	},
	{
		0xca23,
		0,
		"C_USE_ALPHA "
	},
	{
		0xca24,
		0,
		"C_TGA_DEPTH "
	},
	{
		0xca25,
		0,
		"C_REND_FIELDS "
	},
	{
		0xca26,
		0,
		"C_REFLIP "
	},
	{
		0xca27,
		0,
		"C_SEL_ITEMTOG "
	},
	{
		0xca28,
		0,
		"C_SEL_RESET "
	},
	{
		0xca29,
		0,
		"C_STICKY_KEYINF "
	},
	{
		0xca2a,
		0,
		"C_WELD_THRESHOLD "
	},
	{
		0xca2b,
		0,
		"C_ZCLIP_POINT "
	},
	{
		0xca2c,
		0,
		"C_ALPHA_SPLIT "
	},
	{
		0xca30,
		0,
		"C_KF_SHOW_BACKFACE "
	},
	{
		0xca40,
		0,
		"C_OPTIMIZE_LOFT "
	},
	{
		0xca42,
		0,
		"C_TENS_DEFAULT "
	},
	{
		0xca44,
		0,
		"C_CONT_DEFAULT "
	},
	{
		0xca46,
		0,
		"C_BIAS_DEFAULT "
	},
	{
		0xca50,
		0,
		"C_DXFNAME_SRC "
	},
	{
		0xca60,
		0,
		"C_AUTO_WELD "
	},
	{
		0xca70,
		0,
		"C_AUTO_UNIFY "
	},
	{
		0xca80,
		0,
		"C_AUTO_SMOOTH "
	},
	{
		0xca90,
		0,
		"C_DXF_SMOOTH_ANG "
	},
	{
		0xcaa0,
		0,
		"C_SMOOTH_ANG "
	},
	{
		0xcb00,
		0,
		"C_WORK_MTLS_5 "
	},
	{
		0xcb01,
		0,
		"C_WORK_MTLS_6 "
	},
	{
		0xcb02,
		0,
		"C_WORK_MTLS_7 "
	},
	{
		0xcb03,
		0,
		"C_WORK_MTLS_8 "
	},
	{
		0xcb04,
		0,
		"C_WORKMTL "
	},
	{
		0xcb10,
		0,
		"C_SXP_TEXT_DATA "
	},
	{
		0xcb11,
		0,
		"C_SXP_OPAC_DATA "
	},
	{
		0xcb12,
		0,
		"C_SXP_BUMP_DATA "
	},
	{
		0xcb13,
		0,
		"C_SXP_SHIN_DATA "
	},
	{
		0xcb20,
		0,
		"C_SXP_TEXT2_DATA "
	},
	{
		0xcb24,
		0,
		"C_SXP_SPEC_DATA "
	},
	{
		0xcb28,
		0,
		"C_SXP_SELFI_DATA "
	},
	{
		0xcb30,
		0,
		"C_SXP_TEXT_MASKDATA "
	},
	{
		0xcb32,
		0,
		"C_SXP_TEXT2_MASKDATA "
	},
	{
		0xcb34,
		0,
		"C_SXP_OPAC_MASKDATA "
	},
	{
		0xcb36,
		0,
		"C_SXP_BUMP_MASKDATA "
	},
	{
		0xcb38,
		0,
		"C_SXP_SPEC_MASKDATA "
	},
	{
		0xcb3a,
		0,
		"C_SXP_SHIN_MASKDATA "
	},
	{
		0xcb3e,
		0,
		"C_SXP_REFL_MASKDATA "
	},
	{
		0xcc00,
		0,
		"C_NET_USE_VPOST "
	},
	{
		0xcc10,
		0,
		"C_NET_USE_GAMMA "
	},
	{
		0xcc20,
		0,
		"C_NET_FIELD_ORDER "
	},
	{
		0xcd00,
		0,
		"C_BLUR_FRAMES "
	},
	{
		0xcd10,
		0,
		"C_BLUR_SAMPLES "
	},
	{
		0xcd20,
		0,
		"C_BLUR_DUR "
	},
	{
		0xcd30,
		0,
		"C_HOT_METHOD "
	},
	{
		0xcd40,
		0,
		"C_HOT_CHECK "
	},
	{
		0xcd50,
		0,
		"C_PIXEL_SIZE "
	},
	{
		0xcd60,
		0,
		"C_DISP_GAMMA "
	},
	{
		0xcd70,
		0,
		"C_FBUF_GAMMA "
	},
	{
		0xcd80,
		0,
		"C_FILE_OUT_GAMMA "
	},
	{
		0xcd82,
		0,
		"C_FILE_IN_GAMMA "
	},
	{
		0xcd84,
		0,
		"C_GAMMA_CORRECT "
	},
	{
		0xcd90,
		0,
		"C_APPLY_DISP_GAMMA "
	},
	{
		0xcda0,
		0,
		"C_APPLY_FBUF_GAMMA "
	},
	{
		0xcdb0,
		0,
		"C_APPLY_FILE_GAMMA "
	},
	{
		0xcdc0,
		0,
		"C_FORCE_WIRE "
	},
	{
		0xcdd0,
		0,
		"C_RAY_SHADOWS "
	},
	{
		0xcde0,
		0,
		"C_MASTER_AMBIENT "
	},
	{
		0xcdf0,
		0,
		"C_SUPER_SAMPLE "
	},
	{
		0xce00,
		0,
		"C_OBJECT_MBLUR "
	},
	{
		0xce10,
		0,
		"C_MBLUR_DITHER "
	},
	{
		0xce20,
		0,
		"C_DITHER_24 "
	},
	{
		0xce30,
		0,
		"C_SUPER_BLACK "
	},
	{
		0xce40,
		0,
		"C_SAFE_FRAME "
	},
	{
		0xce50,
		0,
		"C_VIEW_PRES_RATIO "
	},
	{
		0xce60,
		0,
		"C_BGND_PRES_RATIO "
	},
	{
		0xce70,
		0,
		"C_NTH_SERIAL_NUM "
	},
	{
		0xd000,
		0,
		"VPDATA "
	},
	{
		0xd100,
		0,
		"P_QUEUE_ENTRY "
	},
	{
		0xd110,
		0,
		"P_QUEUE_IMAGE "
	},
	{
		0xd114,
		0,
		"P_QUEUE_USEIGAMMA "
	},
	{
		0xd120,
		0,
		"P_QUEUE_PROC "
	},
	{
		0xd130,
		0,
		"P_QUEUE_SOLID "
	},
	{
		0xd140,
		0,
		"P_QUEUE_GRADIENT "
	},
	{
		0xd150,
		0,
		"P_QUEUE_KF "
	},
	{
		0xd152,
		0,
		"P_QUEUE_MOTBLUR "
	},
	{
		0xd153,
		0,
		"P_QUEUE_MB_REPEAT "
	},
	{
		0xd160,
		0,
		"P_QUEUE_NONE "
	},
	{
		0xd180,
		0,
		"P_QUEUE_RESIZE "
	},
	{
		0xd185,
		0,
		"P_QUEUE_OFFSET "
	},
	{
		0xd190,
		0,
		"P_QUEUE_ALIGN "
	},
	{
		0xd1a0,
		0,
		"P_CUSTOM_SIZE "
	},
	{
		0xd210,
		0,
		"P_ALPH_NONE "
	},
	{
		0xd220,
		0,
		"P_ALPH_PSEUDO "
	},
	{
		0xd221,
		0,
		"P_ALPH_OP_PSEUDO "
	},
	{
		0xd222,
		0,
		"P_ALPH_BLUR "
	},
	{
		0xd225,
		0,
		"P_ALPH_PCOL "
	},
	{
		0xd230,
		0,
		"P_ALPH_C0 "
	},
	{
		0xd231,
		0,
		"P_ALPH_OP_KEY "
	},
	{
		0xd235,
		0,
		"P_ALPH_KCOL "
	},
	{
		0xd238,
		0,
		"P_ALPH_OP_NOCONV "
	},
	{
		0xd240,
		0,
		"P_ALPH_IMAGE "
	},
	{
		0xd250,
		0,
		"P_ALPH_ALPHA "
	},
	{
		0xd260,
		0,
		"P_ALPH_QUES "
	},
	{
		0xd265,
		0,
		"P_ALPH_QUEIMG "
	},
	{
		0xd270,
		0,
		"P_ALPH_CUTOFF "
	},
	{
		0xd280,
		0,
		"P_ALPHANEG "
	},
	{
		0xd300,
		0,
		"P_TRAN_NONE "
	},
	{
		0xd310,
		0,
		"P_TRAN_IMAGE "
	},
	{
		0xd312,
		0,
		"P_TRAN_FRAMES "
	},
	{
		0xd320,
		0,
		"P_TRAN_FADEIN "
	},
	{
		0xd330,
		0,
		"P_TRAN_FADEOUT "
	},
	{
		0xd340,
		0,
		"P_TRANNEG "
	},
	{
		0xd400,
		0,
		"P_RANGES "
	},
	{
		0xd500,
		0,
		"P_PROC_DATA "
	},
	{
		0xf020,
		0,
		"POS_TRACK_TAG_KEY "
	},
	{
		0xf021,
		0,
		"ROT_TRACK_TAG_KEY "
	},
	{
		0xf022,
		0,
		"SCL_TRACK_TAG_KEY "
	},
	{
		0xf023,
		0,
		"FOV_TRACK_TAG_KEY "
	},
	{
		0xf024,
		0,
		"ROLL_TRACK_TAG_KEY "
	},
	{
		0xf025,
		0,
		"COL_TRACK_TAG_KEY "
	},
	{
		0xf026,
		0,
		"MORPH_TRACK_TAG_KEY "
	},
	{
		0xf027,
		0,
		"HOT_TRACK_TAG_KEY "
	},
	{
		0xf028,
		0,
		"FALL_TRACK_TAG_KEY "
	},
	{
		0xf110,
		0,
		"POINT_ARRAY_ENTRY "
	},
	{
		0xf111,
		0,
		"POINT_FLAG_ARRAY_ENTRY "
	},
	{
		0xf120,
		0,
		"FACE_ARRAY_ENTRY "
	},
	{
		0xf130,
		0,
		"MSH_MAT_GROUP_ENTRY "
	},
	{
		0xf140,
		0,
		"TEX_VERTS_ENTRY "
	},
	{
		0xf150,
		0,
		"SMOOTH_GROUP_ENTRY "
	},
	{
		0xffff,
		0,
		"DUMMY "
	} /* Must be last element */
};

#endif
/*===========================================================================
 *      End of File Chunk3ds.H
 *=========================================================================*/
