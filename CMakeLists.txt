cmake_minimum_required(VERSION 3.31)

# Enable version specification in project command
if (POLICY CMP0048)
	cmake_policy(SET CMP0048 NEW)
endif()

project(MWEdit VERSION 0.7.0
               HOMEPAGE_URL "https://github.com/Walrus-Tech/MWEdit")

set(common_src "common/container/dl_map.cc"
               "common/container/gen_stack.cc"
               "common/container/list_file.cc"
               "common/container/ptr_array.cc"
               "common/container/tem_array.cc"

               "common/file/config_file.cc"
               "common/file/file_buffer.cc"
               "common/file/gen_file.cc"
               "common/file/gen_find.cc"

               "common/images/rgb_pal.cc"

               "common/string/sstring.cc"
               "common/string/sstring_array.cc"

#              "common/time/task_time.cc"

               "common/utility/name_list.cc"
               "common/utility/profile.cc"

               "common/dl_base.cc"
               "common/dl_block.cc"
               "common/dl_chr.cc"
               "common/dl_err.cc"
               "common/dl_file.cc"
               "common/dl_log.cc"
               "common/dl_math.cc"
               "common/dl_mem.cc"
               "common/dl_str.cc"
               "common/dl_time.cc")

set(file_src "file/xml/xml_attribute.cc"
             "file/xml/xml_element.cc"
             "file/xml/xml_file.cc"

             "file/3ds_file.cc"
             "file/bmp_file.cc"
             "file/csv_file.cc"
             "file/dxf_file.cc"
             "file/pcx_file.cc")

set(game_morrowind_src "game/morrowind/activator.cc"
                       "game/morrowind/alchemy.cc"
                       "game/morrowind/apparatus.cc"
                       "game/morrowind/armor.cc"
                       "game/morrowind/birth_sign.cc"
                       "game/morrowind/body_part.cc"
                       "game/morrowind/book.cc"
                       "game/morrowind/cell.cc"
                       "game/morrowind/class.cc"
                       "game/morrowind/clothing.cc"
                       "game/morrowind/container.cc"
                       "game/morrowind/creature.cc"
                       "game/morrowind/defs.cc"
                       "game/morrowind/dialogue.cc"
                       "game/morrowind/door.cc"
                       "game/morrowind/enchant.cc"
                       "game/morrowind/faction.cc"
                       "game/morrowind/file.cc"
                       "game/morrowind/game_setting.cc"
                       "game/morrowind/global.cc"
                       "game/morrowind/info.cc"
                       "game/morrowind/ingredient.cc"
                       "game/morrowind/item_1.cc"
                       "game/morrowind/item_2.cc"
                       "game/morrowind/item_3.cc"
                       "game/morrowind/land.cc"
                       "game/morrowind/level_crea.cc"
                       "game/morrowind/level_item.cc"
                       "game/morrowind/light.cc"
                       "game/morrowind/lock_pick.cc"
                       "game/morrowind/magic_effect.cc"
                       "game/morrowind/misc.cc"
                       "game/morrowind/npc.cc"
                       "game/morrowind/probe.cc"
                       "game/morrowind/race.cc"
                       "game/morrowind/record.cc"
                       "game/morrowind/region.cc"
                       "game/morrowind/repair.cc"
                       "game/morrowind/script.cc"
                       "game/morrowind/skill.cc"
                       "game/morrowind/sound.cc"
                       "game/morrowind/sound_gen.cc"
                       "game/morrowind/spell.cc"
                       "game/morrowind/start_script.cc"
                       "game/morrowind/static.cc"
                       "game/morrowind/sub_base.cc"
                       "game/morrowind/sub_cell_ref.cc"
                       "game/morrowind/sub_name.cc"
                       "game/morrowind/sub_scvr.cc"
                       "game/morrowind/tes3.cc"
                       "game/morrowind/weapon.cc")

set(mwedit_src "mwedit/csv_defs.cc"
               "mwedit/mw_common.cc"
               "mwedit/mw_custom_func.cc"
               "mwedit/options.cc"
               "mwedit/scr_func_array.cc"
               "mwedit/scr_func_data.cc"
               "mwedit/script_compile.cc"
               "mwedit/script_compile_ex.cc"
               "mwedit/script_defs.cc"
               "mwedit/script_error.cc"
               "mwedit/script_funcs.cc"
               "mwedit/script_options.cc"
               "mwedit/script_template.cc"
               "mwedit/std_afx.cc"
               "mwedit/win_utils.cc")

set(ui_src "ui/activator_dlg.cc"
           "ui/ai_activate_dlg.cc"
           "ui/ai_escort_dlg.cc"
           "ui/ai_travel_dlg.cc"
           "ui/ai_wander_dlg.cc"
           "ui/alchemy_dlg.cc"
           "ui/apparatus_dlg.cc"
           "ui/armor_dlg.cc"
           "ui/birth_sign_dlg.cc"
           "ui/body_part_dlg.cc"
           "ui/book_dlg.cc"
           "ui/cell_dlg.cc"
           "ui/cell_ref_dlg.cc"
           "ui/child_frame.cc"
           "ui/child_frame_fix.cc"
           "ui/child_frame_script.cc"
           "ui/child_frame_var.cc"
           "ui/class_dlg.cc"
           "ui/clothing_dlg.cc"
#           "ui/color_static_1.cc"
#           "ui/color_static.cc"
           "ui/contain_dlg.cc"
           "ui/creature_dlg.cc"
           "ui/creature_page_1.cc"
           "ui/creature_page_2.cc"
           "ui/creature_page_3.cc"
           "ui/creature_page_4.cc"
           "ui/creature_page_5.cc"
           "ui/csv_import_dlg.cc"
           "ui/cust_rich_edit.cc"
           "ui/dialog_dlg.cc"
           "ui/dlg_array.cc"
           "ui/door_dlg.cc"
           "ui/edit_undo.cc"
           "ui/effect_dlg.cc"
           "ui/enchant_dlg.cc"
           "ui/error_dialog.cc"
           "ui/ext_cell_page.cc"
           "ui/faction_dlg.cc"
           "ui/find_dlg.cc"
           "ui/func_help_view.cc"
           "ui/global_dlg.cc"
           "ui/glob_options.cc"
           "ui/header_dlg.cc"
           "ui/icon_frame.cc"
           "ui/info_dlg.cc"
           "ui/ingredient_dlg.cc"
           "ui/int_cell_page.cc"
           "ui/journal_dlg.cc"
           "ui/level_crea_dlg.cc"
           "ui/level_item_dlg.cc"
           "ui/light_dlg.cc"
           "ui/list_ctrl.cc"
           "ui/load_dlg.cc"
           "ui/lock_pick_dlg.cc"
           "ui/main_frm.cc"
           "ui/misc_dlg.cc"
           "ui/mwedit_doc.cc"
           "ui/mwedit_view.cc"
           "ui/npc_dlg.cc"
           "ui/npc_page_1.cc"
           "ui/npc_page_2.cc"
           "ui/npc_page_3.cc"
           "ui/npc_page_4.cc"
           "ui/npc_page_5.cc"
           "ui/open_plugin_dlg.cc"
           "ui/options_dlg.cc"
           "ui/probe_dlg.cc"
           "ui/race_dlg.cc"
           "ui/rec_dialog.cc"
           "ui/ref_cell_page.cc"
           "ui/region_dlg.cc"
           "ui/repair_dlg.cc"
           "ui/script_compare_dlg.cc"
           "ui/script_dlg.cc"
           "ui/script_error_dlg.cc"
           "ui/script_error_view.cc"
           "ui/scr_temp_page_1.cc"
           "ui/scr_temp_page_2.cc"
           "ui/scr_temp_page_3.cc"
           "ui/scr_temp_view.cc"
           "ui/setting_dlg.cc"
           "ui/skill_dlg.cc"
           "ui/sound_dlg.cc"
           "ui/sound_gen_dlg.cc"
           "ui/spell_dlg.cc"
           "ui/splitter_wnd.cc"
           "ui/start_script_dlg.cc"
           "ui/static_dlg.cc"
           "ui/sub_list_ctrl.cc"
           "ui/uses_dlg.cc"
           "ui/utils.cc"
           "ui/weapon_dlg.cc")

set(windows_src "windows/color_static.cc"
                "windows/dl_tool_tip.cc"
                "windows/tab_ctrl_sheet.cc"
                "windows/win_util.cc")

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
	                            ${game_morrowind_src}
	                            ${mwedit_src}
	                            ${ui_src}
	                            ${windows_src}
	                            "ui/mwedit.cc")
	# Add required MFC macros
	target_compile_definitions(MWEdit PUBLIC _AFXDLL)
	# Add the Windows resource file
	target_sources(MWEdit PUBLIC "${CMAKE_SOURCE_DIR}/build/windows/mwedit.rc")
else ()
	add_executable(MWEdit ${common_src}
	                      ${file_src}
	                      ${game_morrowind_src}
	                      ${mwedit_src}
	                      ${ui_src}
	                      ${windows_src}
	                      "ui/mwedit.cc")
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

install(FILES "data/customfunctions.dat"
              "data/Functions.dat"
              "data/mweditextrafile.esp"
              "data/MwEditScriptTest.esp"
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
