/************************************************************************
 *   insanemap GIMP plugin
 *
 *   Copyright (C) 2002-2008 Shawn Kirst <skirst@insightbb.com>
 *   Copyright (C) 2013 Omar Emad
 *   Copyright (C) 2013 Derby Russell <jdrussell51@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public
 *   License as published by the Free Software Foundation; either
 *   version 2 of the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; see the file COPYING.  If not, write to
 *   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 *   Boston, MA 02111-1307, USA.
 ************************************************************************/

#include "config.h"
#include "libgimp/stdplugins-intl.h"

#include "InsaneBump.h"
#include "InsaneBumpDialog.h"

static void query(void);
static void run(const gchar *name, gint params, const GimpParam *param,
                gint *nreturn_vals, GimpParam **return_vals);

GimpPlugInInfo PLUG_IN_INFO =
{
   0, 0, query, run
};

#define PLUG_IN_PROC    "plug-in-insanebump"
#define PLUG_IN_BINARY  "InsaneBump"
#define PLUG_IN_VERSION "1.0.0 - 8 November 2013"

/**
 *  Doesn't work with Microsoft Visual Studio 2010 Express C Compiler:
 * NormalmapVals nmapvals =
 * {
 *    .filter = 0,
 *    .minz = 0.0,
 *    .scale = 1.0,
 *    .wrap = 0,
 *    .height_source = 0,
 *    .alpha = ALPHA_NONE,
 *    .conversion = CONVERT_NONE,
 *    .dudv = DUDV_NONE,
 *    .xinvert = 0,
 *    .yinvert = 0,
 *    .swapRGB = 0,
 *    .contrast = 0.0,
 *    .alphamap_id = 0
 * };
 */

NormalmapVals nmapvals =
{
   0,
   0.0,
   1.0,
   0,
   0,
   ALPHA_NONE,
   CONVERT_NONE,
   DUDV_NONE,
   0,
   0,
   0,
   0.0,
   0
};

/**
 * typedef struct
 * {
 *     gint32 RemoveLighting;
 *     gint32 Resizie;
 *     gint32 Tile;
 *     gint32 newWidth;
 *     gint32 EdgeSpecular;
 *     gint32 defSpecular;
 *     gfloat Depth;
 *     gint32 LargeDetails;
 *     gint32 MediumDetails;
 *     gint32 SmallDetails;
 *     gint32 ShapeRecog;
 *     gint32 smoothstep;
 *     gint32 invh;
 *     gint32 ao;
 *     gint32 prev;
 * } InsanemapVals;
 *  * @param RemoveLighting - gint32 BOOL TRUE OR FALSE to remove lighting.
 *  * @param Resizie        - gint32 BOOL TRUE OR FALSE to resize image with a multiple of newWidth Integer.
 *  * @param Tile           - gint32 Tile images BOOL TRUE OR FALSE.
 *  * @param newWidth       - gint32 if Resizie is TRUE this value will increase both the width and height by this factor.
 *  * @param EdgeSpecular   - gint32 Edge Enhancing Specular BOOL TRUE OR FALSE.
 *  * @param defSpecular    - gint32 Specular Definition (0-255)
 *  * @param Depth          - gfloat Depth(+/-)
 *  * @param LargeDetails   - gint32 Large Detail Size (~3).
 *  * @param MediumDetails  - gint32 Medium Detail Intensity(%)
 *  * @param SmallDetails   - gint32 Small Detail Intensity(%)
 *  * @param ShapeRecog     - gint32 Shape Recognition(%)
 *  * @param smoothstep     - gint32 Smooth Step BOOL TRUE OR FALSE
 *  * @param invh           - gint32 Invert Height Map BOOL TRUE OR FALSE
 *  * @param ao             - gint32 ao
 *  * @param prev           - gint32 Preview BOOL TRUE OR FALSE
 *
 *       {GIMP_PDB_INT32, "remove_lighting", "Remove Lighting TRUE or FALSE default FALSE"},
 *       {GIMP_PDB_INT32, "resizie", "Upscale(HD) TRUE or FALSE default FALSE"},
 *       {GIMP_PDB_INT32, "tile", "Tile TRUE or FALSE default TRUE"},
 *       {GIMP_PDB_INT32, "new_width", "New Width(Integer Times larger) default 2"},
 *       {GIMP_PDB_INT32, "edge_specular", "Edge Enhaning Specular TRUE or FALSE default TRUE"},
 *       {GIMP_PDB_INT32, "def_specular", "Specular Definition(0-255) default 64"},
 *       {GIMP_PDB_FLOAT, "depth", "Depth(+/-) default 20.00"},
 *       {GIMP_PDB_INT32, "large_details", "Large Detail Size default 3"},
 *       {GIMP_PDB_INT32, "medium_details", "Medium Detail Intensity(%) default 50"},
 *       {GIMP_PDB_INT32, "small_details", "Small Detail Intensity(%) default 50"},
 *       {GIMP_PDB_INT32, "shape_recog", "Shape Recognition(%) default 50"},
 *       {GIMP_PDB_INT32, "smoothstep", "Smooth Step TRUE or FALSE default TRUE"},
 *       {GIMP_PDB_INT32, "invh", "Invert Height Map TRUE or FALSE default FALSE"},
 *       {GIMP_PDB_INT32, "ao", "ao default 50"},
 *       {GIMP_PDB_INT32, "prev", "Preview TRUE or FALSE default TRUE"}
*/

/** Setup default values here. */
InsanemapVals imapvals =
{
    0,
    0,
    1,
    2,
    1,
    64,
    20.00f,
    3,
    50,
    50,
    50,
    1,
    0,
    50,
    1,
    0
};

MAIN()

static void query(void)
{
   static GimpParamDef args[]=
   {
      {GIMP_PDB_INT32, "run_mode", "Interactive, non-interactive"},
      {GIMP_PDB_IMAGE, "image", "Input image"},
      {GIMP_PDB_DRAWABLE, "drawable", "Input drawable"},
      {GIMP_PDB_INT32, "remove_lighting", "Remove Lighting TRUE or FALSE default FALSE"},
      {GIMP_PDB_INT32, "resizie", "Upscale(HD) TRUE or FALSE default FALSE"},
      {GIMP_PDB_INT32, "tile", "Tile TRUE or FALSE default TRUE"},
      {GIMP_PDB_INT32, "new_width", "New Width(Integer Times larger) default 2"},
      {GIMP_PDB_INT32, "edge_specular", "Edge Enhaning Specular TRUE or FALSE default TRUE"},
      {GIMP_PDB_INT32, "def_specular", "Specular Definition(0-255) default 64"},
      {GIMP_PDB_FLOAT, "depth", "Depth(+/-) default 20.00"},
      {GIMP_PDB_INT32, "large_details", "Large Detail Size default 3"},
      {GIMP_PDB_INT32, "medium_details", "Medium Detail Intensity(%) default 50"},
      {GIMP_PDB_INT32, "small_details", "Small Detail Intensity(%) default 50"},
      {GIMP_PDB_INT32, "shape_recog", "Shape Recognition(%) default 50"},
      {GIMP_PDB_INT32, "smoothstep", "Smooth Step TRUE or FALSE default TRUE"},
      {GIMP_PDB_INT32, "invh", "Invert Height Map TRUE or FALSE default FALSE"},
      {GIMP_PDB_INT32, "ao", "ao default 50"},
      {GIMP_PDB_INT32, "prev", "Preview TRUE or FALSE default TRUE"}
   };

   gimp_install_procedure (PLUG_IN_PROC,
                          N_("Produce images needed for Graphical Rendering"),
                          "This plug-in automatically produces specular, "
                          "normal and other images from current image. ",
                          "Omar Emad & Derby Russell <jdrussell51@gmail.com?>",
                          "GNU Copyright 2013 by Derby Russell",
                          PLUG_IN_VERSION,
                          N_("_InsaneBump..."),
                          "RGB*, GRAY*",
                          GIMP_PLUGIN,
                          G_N_ELEMENTS (args), 0,
                          args, NULL);
                          
    gimp_plugin_menu_register (PLUG_IN_PROC,
                                "<Image>/Filters/Map");
                  
/**
 * Notes here on PF_BOOL
 * In GIMP Plugin development for C language you would NOT use PF_BOOL ofcourse.
 * You would use GIMP_PDB_INT32.
 * 
 * I found the following that corresponds to this in gvaluetypes.h in c:\gtk\include\glib-2.0\gobject:
 * 
 *   * G_VALUE_HOLDS_BOOLEAN:
 *   * @value: a valid #GValue structure
 *   * 
 *   * Checks whether the given #GValue can hold values of type %G_TYPE_BOOLEAN.
 *   * 
 *   * Returns: %TRUE on success.
 *   
 *  define G_VALUE_HOLDS_BOOLEAN(value)	 (G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_BOOLEAN))
 * 
 * AND in the file plug-in-params.c in c:\gimp-2.6.11\app\plug-in:
 * 
 * GValueArray *
 * plug_in_params_to_args (GParamSpec **pspecs,
 *                         gint         n_pspecs,
 *                         GPParam     *params,
 *                         gint         n_params,
 *                        gboolean     return_values,
 *                         gboolean     full_copy)
 * 
 *   ...
 * 
 * GType  type;
 * 
 *   ...
 * 
 *     *  first get the fallback compat GType that matches the pdb type  *
 *     type = gimp_pdb_compat_arg_type_to_gtype (params[i].type);
 * 
 *   ...
 * 
 * g_value_init (&value, type);
 * 
 *   ...
 * 
 *         case GIMP_PDB_INT32:
 *           if (G_VALUE_HOLDS_INT (&value))
 *             g_value_set_int (&value, params[i].data.d_int32);
 *           else if (G_VALUE_HOLDS_UINT (&value))
 *             g_value_set_uint (&value, params[i].data.d_int32);
 *           else if (G_VALUE_HOLDS_ENUM (&value))
 *             g_value_set_enum (&value, params[i].data.d_int32);
 *           else if (G_VALUE_HOLDS_BOOLEAN (&value))
 *             g_value_set_boolean (&value, params[i].data.d_int32 ? TRUE : FALSE);
 *           else
 *             {
 *               g_printerr ("%s: unhandled GIMP_PDB_INT32 type: %s\n",
 *                           G_STRFUNC, g_type_name (G_VALUE_TYPE (&value)));
 *               g_return_val_if_reached (args);
 *             }
 *           break;
 * 
 *    "InsaneBump", "", "", "", "", "",
 *    "<Image>/Filters/Map/Insane...", "",
 *    [
 *    (PF_BOOL, "RemoveLighting", "Remove Lighting", FALSE),
 *    (PF_BOOL, "Reszie", "Upscale(HD)", FALSE),
 *    (PF_BOOL, "Tile", "Tile", TRUE),
 *    (PF_INT32, "newWidth", "New Width(Integer Times larger)", 2),
 *    (PF_BOOL, "EdgeSpecular", "Edge Enhaning Specular", TRUE),
 *    (PF_INT32, "defSpecular", "Specular Definition(0-255)", 64),
 *    (PF_FLOAT, "Depth", "Depth(+/-)", 20),
 *    (PF_INT32, "LargeDetails", "Large Detail Size", 3),
 *    (PF_INT32, "MediumDetails", "Medium Detail Intensity(%)", 50),
 *    (PF_INT32, "SmallDetails", "Small Detail Intensity(%)", 50),
 *    (PF_INT32, "ShapeRecog", "Shape Recognition(%)", 50),
 *    (PF_BOOL, "smoothstep", "Smooth Step", TRUE),
 *    (PF_BOOL, "invh", "Invert Height Map", False),
 *    (PF_INT32, "ao", "ao", 50),
 *    (PF_BOOL, "prev", "Preview", TRUE)
 *    ],
 *    [],
 *    batchnr
 *    )
*/

}

static void run(const gchar *name, gint nparams, const GimpParam *param,
                gint *nreturn_vals, GimpParam **return_vals)
{
   static GimpParam values[1];
   GimpDrawable *drawable;
   GimpRunMode run_mode;
   GimpPDBStatusType status = GIMP_PDB_SUCCESS;
   gint32 drawable_ID = param[1].data.d_drawable;
   gint nDlgResponse = -5;
   
   imapvals.image_ID = drawable_ID;
   
   run_mode = param[0].data.d_int32;
   
   INIT_I18N();
   
   *nreturn_vals = 1;
   *return_vals = values;
   
   values[0].type = GIMP_PDB_STATUS;
   values[0].data.d_status = status;
   
   drawable = gimp_drawable_get(param[2].data.d_drawable);
   gimp_tile_cache_ntiles (2 * drawable->ntile_cols);
   
   switch(run_mode)
   {
      case GIMP_RUN_INTERACTIVE:
         gimp_ui_init(PLUG_IN_BINARY, 0);
         gimp_get_data(PLUG_IN_PROC, &imapvals);
         nDlgResponse = InsaneBumpDialog(drawable, PLUG_IN_BINARY);
         switch(nDlgResponse)
         {
             case 0:
                status = GIMP_PDB_EXECUTION_ERROR;
                values[0].data.d_status = status;
                gimp_drawable_detach(drawable);
                return;
             case 1:
                gimp_set_data(PLUG_IN_PROC, &imapvals, sizeof(imapvals));
             default:
                values[0].data.d_status = status;
                gimp_drawable_detach(drawable);
                gimp_displays_flush();
                return;
         }
         break;
      case GIMP_RUN_NONINTERACTIVE:
         if(nparams != 17)
            status=GIMP_PDB_CALLING_ERROR;
         else
         {
             imapvals.RemoveLighting = param[3].data.d_int32;
             imapvals.Resizie = param[4].data.d_int32;
             imapvals.Tile = param[5].data.d_int32;
             imapvals.newWidth = param[6].data.d_int32;
             imapvals.EdgeSpecular = param[7].data.d_int32;
             imapvals.defSpecular = param[8].data.d_int32;
             imapvals.Depth = param[9].data.d_float;
             imapvals.LargeDetails = param[10].data.d_int32;
             imapvals.MediumDetails = param[11].data.d_int32;
             imapvals.SmallDetails = param[12].data.d_int32;
             imapvals.ShapeRecog = param[13].data.d_int32;
             imapvals.smoothstep = param[14].data.d_int32;
             imapvals.invh = param[15].data.d_int32;
             imapvals.ao = param[16].data.d_int32;
             imapvals.prev = param[17].data.d_int32;
         }
         break;
      case GIMP_RUN_WITH_LAST_VALS:
         gimp_get_data(PLUG_IN_PROC, &imapvals);
         break;
      default:
         break;
   }
   
   gimp_progress_init("Creating InsaneBump...");
   
   if (batchnr(drawable_ID, 1) == 0)
       status = GIMP_PDB_EXECUTION_ERROR;
   
   if(run_mode != GIMP_RUN_NONINTERACTIVE)
      gimp_displays_flush();
   
   if(run_mode == GIMP_RUN_INTERACTIVE)
      gimp_set_data(PLUG_IN_PROC, &imapvals, sizeof(imapvals));
   
   values[0].data.d_status = status;
   
   gimp_drawable_detach(drawable);
}
