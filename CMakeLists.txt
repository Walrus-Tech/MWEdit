cmake_minimum_required(VERSION 3.31)

# Enable version specification in project command
if (POLICY CMP0048)
	cmake_policy(SET CMP0048 NEW)
endif()

project(MWEdit VERSION 0.7.0
               HOMEPAGE_URL "https://github.com/Walrus-Tech/MWEdit")

set(common_src "Common/Contain/GenStack.cpp"
               "Common/Contain/listfile.cpp"
               "Common/Contain/PtrArray.cpp"
               "Common/Contain/temarray.cpp"
               "Common/File/CfgFile.cpp"
               "Common/File/FileBuffer.cpp"
               "Common/File/GenFile.cpp"
               "Common/File/GenFind.cpp"
               "Common/Images/rgbpal.cpp"
               "Common/String/SSArray.cpp"
               "Common/String/SString.cpp"
#              "Common/Time/tasktime.cpp"
               "Common/Utility/namelist.cpp"
               "Common/Utility/profile.cpp"
               "Common/dl_base.cpp"
               "Common/dl_block.cpp"
               "Common/dl_chr.cpp"
               "Common/dl_err.cpp"
               "Common/dl_file.cpp"
               "Common/dl_log.cpp"
               "Common/dl_math.cpp"
               "Common/dl_mem.cpp"
               "Common/dl_str.cpp"
               "Common/dl_time.cpp")

set(file_src "File/XML/XMLFile.cpp"
             "File/XML/XmlAttr.cpp"
             "File/XML/XmlElem.cpp"
             "File/CsvFile.cpp"
             "File/bmpfile.cpp"
             "File/dxffile.cpp"
             "File/file3ds.cpp"
             "File/pcx.cpp")

set(windows_src "Windows/TabCtrlSheet.cpp"
                "Windows/WinUtil.cpp"
                "Windows/dl_ToolTip.cpp")

set(esm_src "esm/EsmActivator.cpp"
            "esm/EsmAlchemy.cpp"
            "esm/EsmApparatus.cpp"
            "esm/EsmArmor.cpp"
            "esm/EsmBase.cpp"
            "esm/EsmBirthSign.cpp"
            "esm/EsmBodyPart.cpp"
            "esm/EsmBook.cpp"
            "esm/EsmCell.cpp"
            "esm/EsmClass.cpp"
            "esm/EsmClothing.cpp"
            "esm/EsmContainer.cpp"
            "esm/EsmCreature.cpp"
            "esm/EsmDialogue.cpp"
            "esm/EsmDoor.cpp"
            "esm/EsmEnchant.cpp"
            "esm/EsmFaction.cpp"
            "esm/EsmFile.cpp"
            "esm/EsmGameSetting.cpp"
            "esm/EsmGlobal.cpp"
            "esm/EsmInfo.cpp"
            "esm/EsmIngrediant.cpp"
            "esm/EsmItem1.cpp"
            "esm/EsmItem2.cpp"
            "esm/EsmItem3.cpp"
            "esm/EsmLand.cpp"
            "esm/EsmLevelCrea.cpp"
            "esm/EsmLevelItem.cpp"
            "esm/EsmLight.cpp"
            "esm/EsmLockPick.cpp"
            "esm/EsmMagicEffect.cpp"
            "esm/EsmMisc.cpp"
            "esm/EsmNpc.cpp"
            "esm/EsmProbe.cpp"
            "esm/EsmRace.cpp"
            "esm/EsmRecord.cpp"
            "esm/EsmRegion.cpp"
            "esm/EsmRepair.cpp"
            "esm/EsmScript.cpp"
            "esm/EsmSkill.cpp"
            "esm/EsmSound.cpp"
            "esm/EsmSoundGen.cpp"
            "esm/EsmSpell.cpp"
            "esm/EsmStartScript.cpp"
            "esm/EsmStatic.cpp"
            "esm/EsmSubBase.cpp"
            "esm/EsmSubCellRef.cpp"
            "esm/EsmSubName.cpp"
            "esm/EsmSubSCVR.cpp"
            "esm/EsmTES3.cpp"
            "esm/EsmWeapon.cpp"
            "esm/EsmWinUtils.cpp"
            "esm/mwcommon.cpp")

set(project_src "project/ActivatorDlg.cpp"
                "project/ChildFrm.cpp"
                "project/ChildFrmFix.cpp"
                "project/ChildFrmScript.cpp"
                "project/ChildFrmVar.cpp"
                "project/ColorStatic1.cpp"
                "project/CreaturePage1.cpp"
                "project/CreaturePage2.cpp"
                "project/CustRichEdit.cpp"
                "project/ErrorDialog.cpp"
                "project/EsmAiActivateDlg.cpp"
                "project/EsmAiEscortDlg.cpp"
                "project/EsmAiTravelDlg.cpp"
                "project/EsmAiWanderDlg.cpp"
                "project/EsmAlchemyDlg.cpp"
                "project/EsmApparatusDlg.cpp"
                "project/EsmArmorDlg.cpp"
                "project/EsmBirthSignDlg.cpp"
                "project/EsmBodyPartDlg.cpp"
                "project/EsmBookDlg.cpp"
                "project/EsmCellDlg.cpp"
                "project/EsmCellRefDlg.cpp"
                "project/EsmClassDlg.cpp"
                "project/EsmClothingDlg.cpp"
                "project/EsmContainDlg.cpp"
                "project/EsmCreatureDlg.cpp"
                "project/EsmCreaturePage1.cpp"
                "project/EsmCreaturePage2.cpp"
                "project/EsmCreaturePage3.cpp"
                "project/EsmCreaturePage4.cpp"
                "project/EsmCreaturePage5.cpp"
                "project/EsmCsvDefs.cpp"
                "project/EsmCsvImportDlg.cpp"
                "project/EsmDialogDlg.cpp"
                "project/EsmDlgArray.cpp"
                "project/EsmDoorDlg.cpp"
                "project/EsmEffectDlg.cpp"
                "project/EsmEnchantDlg.cpp"
                "project/EsmExtCellPage.cpp"
                "project/EsmFactionDlg.cpp"
                "project/EsmFindDlg.cpp"
                "project/EsmFuncHelpView.cpp"
                "project/EsmGlobOptions.cpp"
                "project/EsmGlobalDlg.cpp"
                "project/EsmHeaderDlg.cpp"
                "project/EsmIconFrame.cpp"
                "project/EsmInfoDlg.cpp"
                "project/EsmIngrediantDlg.cpp"
                "project/EsmIntCellPage.cpp"
                "project/EsmJournalDlg.cpp"
                "project/EsmLevelCreaDlg.cpp"
                "project/EsmLevelItemDlg.cpp"
                "project/EsmLightDlg.cpp"
                "project/EsmListCtrl.cpp"
                "project/EsmLoadDlg.cpp"
                "project/EsmLockPickDlg.cpp"
                "project/EsmMiscDlg.cpp"
                "project/EsmNpcDlg.cpp"
                "project/EsmNpcPage1.cpp"
                "project/EsmNpcPage2.cpp"
                "project/EsmNpcPage3.cpp"
                "project/EsmNpcPage4.cpp"
                "project/EsmNpcPage5.cpp"
                "project/EsmOptions.cpp"
                "project/EsmOptionsDlg.cpp"
                "project/EsmProbeDlg.cpp"
                "project/EsmRaceDlg.cpp"
                "project/EsmRecDialog.cpp"
                "project/EsmRefCellPage.cpp"
                "project/EsmRegionDlg.cpp"
                "project/EsmRepairDlg.cpp"
                "project/EsmScrFuncArray.cpp"
                "project/EsmScrFuncData.cpp"
                "project/EsmScrTempPage1.cpp"
                "project/EsmScrTempPage2.cpp"
                "project/EsmScrTempPage3.cpp"
                "project/EsmScrTempView.cpp"
                "project/EsmScriptCompareDlg.cpp"
                "project/EsmScriptCompile.cpp"
                "project/EsmScriptCompileEx.cpp"
                "project/EsmScriptDefs.cpp"
                "project/EsmScriptDlg.cpp"
                "project/EsmScriptError.cpp"
                "project/EsmScriptFuncs.cpp"
                "project/EsmScriptOptions.cpp"
                "project/EsmSettingDlg.cpp"
                "project/EsmSkillDlg.cpp"
                "project/EsmSoundDlg.cpp"
                "project/EsmSoundGenDlg.cpp"
                "project/EsmSpellDlg.cpp"
                "project/EsmStartScriptDlg.cpp"
                "project/EsmStaticDlg.cpp"
                "project/EsmSubListCtrl.cpp"
                "project/EsmUsesDlg.cpp"
                "project/EsmUtils.cpp"
                "project/EsmWeaponDlg.cpp"
                "project/InputDialog.cpp"
                "project/MWEditDoc.cpp"
                "project/MWEditView.cpp"
                "project/MainFrm.cpp"
                "project/OpenPluginDlg.cpp"
                "project/ScriptErrorDlg.cpp"
                "project/ScriptErrorView.cpp"
                "project/ScriptTemplate.cpp"
                "project/StdAfx.cpp"
                "project/editundo.cpp"
                "project/mwcustomfunc.cpp"
                "project/splitterwnd.cpp")

# Find and set up MFC on Windows
if (WIN32)
	find_package(MFC)

	if (MFC_FOUND)
		# Use shared MFC libraries
		set(CMAKE_MFC_FLAG 2)
	else ()
		message(FATAL_ERROR "MFC Not Found")
	endif ()
endif ()

if (WIN32)
	# If building on Windows, set the GUI application flag
	add_executable(MWEdit WIN32 ${common_src}
	                            ${file_src}
	                            ${windows_src}
	                            ${esm_src}
	                            ${project_src}
	                            "project/MWEdit.cpp")
	# Add required MFC macros
	target_compile_definitions(MWEdit PUBLIC _AFXDLL)
	# Add the Windows resource file
	target_sources(MWEdit PUBLIC "${CMAKE_SOURCE_DIR}/project/MWEdit.rc")
else ()
	add_executable(MWEdit ${common_src}
	                      ${file_src}
	                      ${windows_src}
	                      ${esm_src}
	                      ${project_src}
	                      "project/MWEdit.cpp")
endif ()

# Enable all compiler warnings
if (MSVC)
	target_compile_options(MWEdit PRIVATE /Wall)
else ()
	target_compile_options(MWEdit PRIVATE -Wall -Wextra -Wpedantic)
endif ()

# Find and link the image library
find_package(DevIL)
if (DevIL_ILUT_FOUND)
	target_link_libraries(MWEdit PUBLIC DevIL::IL
	                                    DevIL::ILU
	                                    DevIL::ILUT)
else ()
	# Use Bundled DevIL if not found on the system
	set(il_libs "DevIL"
	            "ILU"
	            "ILUT")
	target_link_directories(MWEdit PUBLIC "${CMAKE_SOURCE_DIR}/IL")
	target_link_libraries(MWEdit PUBLIC ${il_libs})
endif ()

# Set C++ standard to C++20
target_compile_features(MWEdit PUBLIC cxx_std_20)
target_include_directories(MWEdit PUBLIC "${CMAKE_SOURCE_DIR}")
install(TARGETS MWEdit DESTINATION .)

if (WIN32)
	install(FILES "IL/DevIL.dll"
	              "IL/ILU.dll"
	              "IL/ILUT.dll"
	        DESTINATION .)
endif ()

install(FILES "project/customfunctions.dat"
              "project/Functions.dat"
              "project/mweditextrafile.esp"
              "project/MwEditScriptTest.esp"
        DESTINATION .)

if (WIN32)
	# Set the format for installers
	set(CPACK_GENERATOR WIX)
endif ()

set(CPACK_PACKAGE_VENDOR "Walrus Technologies")
set(CPACK_PACKAGE_DESCRIPTION "An alternative Morrowind plugin editor")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/project/res/MWEdit.ico")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_EXECUTABLES "MWEdit" "MWEdit")
set(CPACK_CREATE_DESKTOP_LINKS MWEdit)

if (WIN32)
	set(CPACK_WIX_UPGRADE_GUID "1F54561E-59B9-4E81-AD80-797B9CACA41D")
#	set(CPACK_WIX_LICENSE_RTF "${CMAKE_SOURCE_DIR}/LICENSE.txt")
	set(CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/project/res/MWEdit.ico")
#	set_property(INSTALL $<TARGET_FILE_NAME:MWEdit>
#	             PROPERTY CPACK_START_MENU_SHORTCUTS "MWEdit")
#	set_property(INSTALL $<TARGET_FILE_NAME:MWEdit>
#	             PROPERTY CPACK_DESKTOP_SHORTCUTS "MWEdit")
endif ()

include(CPack)
