/************************************************************************
 *   insanemap GIMP plugin
 *
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

#include <glib.h>

#include "InsaneBump.h"
#include "PluginConnectors.h"

/** Preview window in dialog box is not enabled in this first release. */
// extern GtkWidget *preview;

extern GtkWidget *progress;
extern GtkWidget *progress_label;

/**
 * Builds a file name from the suffix.
 * 
 * Uses memory math.
 * 
 * Pointer szStr points to the memory location at the beginning
 * of the given filename.
 * 
 * Pointer szPtr points to the memory location at the decimal point.
 * 
 * The decimal point will always, in this case, be at a memory
 * location farther down than the start which means the decimal point
 * is located at a memory location value higher than the start.
 * 
 * So, for fence.bmp at 0x003000 the decimal point would be at
 * 0x003005 there for subtract 0x003000 from 0x003005 and 
 * you will get location 5 in the string
 * 
 * Then if you insert a "_n" as a suffix you will get filename:
 * fence_n.bmp!
 */
GString *getFilename(const gchar *filename, const gchar *suffix)
{
    GString * newfilename = g_string_new(filename);
    gchar *szStr = newfilename->str;
    char *szPtr = strchr((char *)szStr, '.');
    int nLocate = szPtr - szStr;
    g_string_insert(newfilename, nLocate, suffix);
	return newfilename;
}

void saveLastOperation(gint32 image_ID, const GString *filename)
{
	gint32 layer_ID = gimp_image_get_active_layer(image_ID);
	gimp_file_save(GIMP_RUN_NONINTERACTIVE, image_ID, layer_ID, filename->str, filename->str);
}

void set_progress_label_as_file(GString *file_name_given, const gchar *szSuffix)
{
    GString *string_temp = g_string_new(file_name_given->str);
    gchar *szStr = string_temp->str;
    char *szPtr = strrchr((char *)szStr, '\\');
    if (szPtr == NULL)
    {
        /** Probably Not Windows. Linux? */
        szPtr = strrchr((char *)szStr, '/');
    }
    if (szPtr != NULL)
    {
        szPtr++ ;
        GString *string_sub = g_string_new(szPtr);
        
        g_string_printf(string_temp, "Saving %s %s", szSuffix, string_sub->str);
        gtk_label_set_text(GTK_LABEL(progress_label), string_temp->str);
        g_string_free(string_temp, TRUE);
    }
    else
    {
        g_string_printf(string_temp, "Saving %s %s", szSuffix, file_name_given->str);
        gtk_label_set_text(GTK_LABEL(progress_label), string_temp->str);
        g_string_free(string_temp, TRUE);
    }
}

gint32 specularEdge(gint32 image_ID, const gchar *file_name, gint defin)
{
    GString *file_name_temp = getFilename(file_name, "_s");
	gint32 drawable_ID = gimp_image_get_active_layer(image_ID);
	gint32 newlayer_ID = gimp_layer_copy (drawable_ID);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.92);
	gimp_image_add_layer(image_ID, newlayer_ID, -1);
	gimp_image_set_active_layer(image_ID, newlayer_ID);
	gimp_desaturate(newlayer_ID);

	drawable_ID = gimp_image_get_active_layer(image_ID);
	newlayer_ID = gimp_layer_copy (drawable_ID);
	gimp_image_add_layer(image_ID, newlayer_ID, -1);
	gimp_image_set_active_layer(image_ID, newlayer_ID);
	gimp_desaturate(newlayer_ID);
    
    /**
     * Filter "Difference of Gaussians" applied
     * Standard plug-in. Source code ships with GIMP.
     * 
     * Add the "f" here to signify float in c language.
     */
	if (plug_in_dog_connector(image_ID, newlayer_ID, 1.0, 8.0, 1, 0) != 1) return 0;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.94);
    
    /**
     * Originally removed by Omar Emad
     * 
     * plug_in_vinvert(image_ID,newlayer_ID);
     */    
    
	gimp_layer_set_mode(newlayer_ID, 7);
	gimp_image_merge_down(image_ID, newlayer_ID, 0);
	drawable_ID = gimp_image_get_active_layer(image_ID);
	gimp_brightness_contrast(drawable_ID, 0, 64);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.96);

	gimp_levels(drawable_ID, 0, defin, 255, 1, 0, 255);
    set_progress_label_as_file(file_name_temp, "_s");
	gimp_file_save(GIMP_RUN_NONINTERACTIVE, image_ID, drawable_ID, file_name_temp->str, file_name_temp->str);
    g_string_free(file_name_temp, TRUE);
	gimp_edit_clear(drawable_ID);
    
    return 1;
}	

gint32 specularSmooth(gint32 image_ID, const gchar *file_name, gint defin)
{
    GString *file_name_temp = getFilename(file_name, "_s");
	gint32 drawable_ID = gimp_image_get_active_layer(image_ID);
	gint32 newlayer_ID = gimp_layer_copy (drawable_ID);
	gimp_image_add_layer(image_ID, newlayer_ID, -1);
	gimp_image_set_active_layer(image_ID, newlayer_ID);
	gimp_desaturate(newlayer_ID);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.92);

	drawable_ID = gimp_image_get_active_layer(image_ID);
	newlayer_ID = gimp_layer_copy (drawable_ID);
	gimp_image_add_layer(image_ID, newlayer_ID, -1);
	gimp_image_set_active_layer(image_ID, newlayer_ID);
	gimp_desaturate(newlayer_ID);

    /**
     * Filter "Difference of Gaussians" applied
     * Standard plug-in. Source code ships with GIMP.
     * 
     * Add the "f" here to signify float in c language.
     */
	if (plug_in_dog_connector(image_ID, newlayer_ID, 8.0f, 1.0f, 1, 0) != 1) return 0;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.94);

    /**
     * Originally removed by Omar Emad
     * 
     * plug_in_vinvert(image_ID,newlayer);
     */    
	
	gimp_layer_set_mode(newlayer_ID, 7);
	gimp_image_merge_down(image_ID, newlayer_ID, 0);
	
	drawable_ID = gimp_image_get_active_layer(image_ID);
	gimp_brightness_contrast(drawable_ID, 0, 64);
	gimp_levels(drawable_ID, 0, defin, 255, 1, 0, 255);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.96);
	gimp_image_raise_layer_to_top(image_ID, drawable_ID);
    set_progress_label_as_file(file_name_temp, "_s");
	gimp_file_save(GIMP_RUN_NONINTERACTIVE, image_ID, drawable_ID, file_name_temp->str, file_name_temp->str);
    g_string_free(file_name_temp, TRUE);
	gimp_edit_clear(drawable_ID);
    
    return 1;
}

void removeShading(gint32 image_ID)
{
	gint32 drawable_ID = gimp_image_get_active_layer(image_ID);
	gint32 newlayer_ID = gimp_layer_copy (drawable_ID);
	gimp_image_add_layer(image_ID, newlayer_ID, -1);
	gimp_image_set_active_layer(image_ID, newlayer_ID);

    /**
     * Filter "Gaussian Blur" applied
     * Standard plug-in. Source code ships with GIMP.
     * 
     * Add the "f" here to signify float in c language.
     */
	if (plug_in_gauss_connector(image_ID, newlayer_ID, 20.0f, 20.0f, 0) != 1) return;

    /**
     * Colors Menu->Invert
     * Standard plug-in. Source code ships with GIMP.
     */
	if (plug_in_vinvert_connector(image_ID, newlayer_ID) != 1) return;

	gimp_layer_set_mode(newlayer_ID, 5);
	gimp_image_merge_visible_layers(image_ID, 0);
}

void blur(gint32 image_ID, gint32 diffuse_ID, gfloat width, gfloat height, gint32 passes, gint32 normal)
{
    gint32 drawable_ID = 0 ;
    gint32 i = 0 ;
	gint32 desatdiffuse_ID = gimp_layer_copy (diffuse_ID);
	gimp_image_add_layer(image_ID, desatdiffuse_ID, -1);
	gimp_image_set_active_layer(image_ID, desatdiffuse_ID);
	if (normal == 0)
    {
		gimp_desaturate(desatdiffuse_ID);
    }

	for (i = 0; i < passes; i++)
    {
		drawable_ID = gimp_image_get_active_layer(image_ID);
		gint32 newlayer_ID = gimp_layer_copy (drawable_ID);
		gimp_image_add_layer(image_ID, newlayer_ID, -1);
		gimp_image_set_active_layer(image_ID, newlayer_ID);
        
        /**
         * Filter "Gaussian Blur" applied
         * Standard plug-in. Source code ships with GIMP.
         * 
         * Add the "f" here to signify float in c language.
         */
        if (plug_in_gauss_connector(image_ID, newlayer_ID, width * 0.05f, height * 0.05f, 0) != 1) return;

		gimp_layer_set_mode(newlayer_ID, 5);
		gimp_image_merge_down(image_ID, newlayer_ID, 0);
		drawable_ID = gimp_image_get_active_layer(image_ID);
    }
    
	if (normal == 1)
    {
        /**
         * Filter "Normalmap" applied
         * Non-Standard plug-in. Source code included.
         * 
         * original values:
		 * plug_in_normalmap_derby(image_ID, drawable_ID, 0, 0.0f, 1.0f, 0, 0, 0, 8, 0, 0, 0, 0, 0.0f, drawable_ID)
         */
        nmapvals.filter = 0;
        nmapvals.minz = 0.0f;
        nmapvals.scale = 1.0f;
        nmapvals.wrap = 0;
        nmapvals.height_source = 0;
        nmapvals.alpha = 0;
        nmapvals.conversion = 8;
        nmapvals.dudv = 0;
        nmapvals.xinvert = 0;
        nmapvals.yinvert = 0;
        nmapvals.swapRGB = 0;
        nmapvals.contrast = 0.0f;
        nmapvals.alphamap_id = drawable_ID;
        normalmap(drawable_ID, 0);

		gimp_layer_set_mode(drawable_ID, 5);
		gimp_image_merge_down(image_ID, drawable_ID, 0);
    }
}				

void sharpen(gint32 image_ID, gint32 diffuse, gfloat depth, gint32 filterSize, gdouble strength)
{
	gint32 sharpnormal_ID = gimp_layer_copy (diffuse);
	gimp_image_add_layer(image_ID, sharpnormal_ID, -1);
	gimp_image_set_active_layer(image_ID, sharpnormal_ID);
	
    /**
     * Filter "Normalmap" applied
     * Non-Standard plug-in. Source code included.
     * 
     * original values:
     * plug_in_normalmap_derby(image_ID, sharpnormal_ID, 0, 0.0, depth, filterSize, 0, 0, 0, 0, 0, 1, 0, 0.0, sharpnormal_ID);
     */
    nmapvals.filter = 0;
    nmapvals.minz = 0.0f;
    nmapvals.scale = depth;
    nmapvals.wrap = filterSize;
    nmapvals.height_source = 0;
    nmapvals.alpha = 0;
    nmapvals.conversion = 0;
    nmapvals.dudv = 0;
    nmapvals.xinvert = 0;
    nmapvals.yinvert = 1;
    nmapvals.swapRGB = 0;
    nmapvals.contrast = 0.0f;
    nmapvals.alphamap_id = sharpnormal_ID;
    normalmap(sharpnormal_ID, 0);

    /**
     * Originally removed by Omar Emad
     * 
     * gimp_levels_stretch(sharpnormal_ID);
     */    

	gimp_image_set_active_layer(image_ID, sharpnormal_ID);
	gimp_layer_set_mode(sharpnormal_ID, 5);

    /**
     * Originally removed by Omar Emad
     * 
     * gimp_file_save(image, sharpnormal_ID, getFilename(file_name, "_hn"), getFilename(file_name, "_hn"));
     */    

	gimp_layer_set_opacity(sharpnormal_ID, strength);
	gimp_image_raise_layer_to_top(image_ID, sharpnormal_ID);
}

void shapeRecognise(gint32 image_ID, gint32 normalmap_ID, gdouble strength)
{
	gint32 blurnormal_ID = gimp_layer_copy(normalmap_ID);
	gimp_image_add_layer(image_ID, blurnormal_ID, -1);
	gimp_image_set_active_layer(image_ID, blurnormal_ID);

    /**
     * Filter "Gaussian Blur" applied
     * Standard plug-in. Source code ships with GIMP.
     * 
     * Add the ".0f" here to signify float in c language.
     */
    if (plug_in_gauss_connector(image_ID, blurnormal_ID, 20.0f, 20.0f, 0) != 1) return;

    /**
     * Colors ->  Components -> "Channel Mixer" applied
     * Standard plug-in. Source code ships with GIMP.
     * 
     * Add the "f" here to signify float in c language.
     * Removed 0.0 on first param and changed to 0 because boolean.
     */
	if (plug_in_colors_channel_mixer_connector(image_ID, blurnormal_ID, 0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -200.0f) != 1) return;

    /**
     * Filter "Normalmap" applied
     * Non-Standard plug-in. Source code included.
     * 
     * original values:
     * plug_in_normalmap_derby(image_ID, blurnormal_ID, 0, 0.0, 1.0, 0, 0, 0, 8, 0, 0, 0, 0, 0.0, blurnormal_ID);
     */
    nmapvals.filter = 0;
    nmapvals.minz = 0.0f;
    nmapvals.scale = 1.0f;
    nmapvals.wrap = 0;
    nmapvals.height_source = 0;
    nmapvals.alpha = 0;
    nmapvals.conversion = 8;
    nmapvals.dudv = 0;
    nmapvals.xinvert = 0;
    nmapvals.yinvert = 0;
    nmapvals.swapRGB = 0;
    nmapvals.contrast = 0.0f;
    nmapvals.alphamap_id = blurnormal_ID;
    normalmap(blurnormal_ID, 0);

    /**
     * Colors ->  Components -> "Channel Mixer" applied
     * Standard plug-in. Source code ships with GIMP.
     * 
     * Add the "f" here to signify float in c language.
     * Removed 0.0 on first param and changed to 0 because boolean.
     */
    if (plug_in_colors_channel_mixer_connector(image_ID, blurnormal_ID, 0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -200.0f) != 1) return;

	gimp_layer_set_mode(blurnormal_ID, 5);
	gimp_layer_set_opacity(blurnormal_ID, strength);
}
	
// not used anywhere ... commenting out (Derby Russell)
//void analyze(gint32 layer_ID)
//{
//	gboolean highlights = gimp_histogram(layer_ID, 0, 179, 256, NULL, NULL, NULL, NULL, NULL, NULL);
//	gboolean midtones = gimp_histogram(layer_ID, 0, 77, 178, NULL, NULL, NULL, NULL, NULL, NULL);
//	gboolean shadows = gimp_histogram(layer_ID, 0, 0, 76, NULL, NULL, NULL, NULL, NULL, NULL);
//	FILE *hFile = fopen("aidata.txt", "w");
//  GString *strTemp = g_string_new("");
//  g_string_printf(strTemp, "%d %d %d", shadows[0], shadows[1], shadows[5]);
//  strcpy(strTemp, itoa();
//  fwrite(str(int(shadows[0])) + " " + str(int(shadows[1])) + " " + str(int(shadows[5] * 100)) + " ")
//	fwrite(str(int(midtones[0])) + " " + str(int(midtones[1])) + " " + str(int(midtones[5] * 100)) + " ")
//	fwrite(str(int(highlights[0])) + " " + str(int(highlights[1])) + " " + str(int(highlights[5] * 100)) + " ")
//}

void doBaseMap(gint32 image_ID, gint32 diffuse_ID, gfloat Depth, gint32 passes)
{
    gint32 i = 0 ;
	for (i = 0; i < passes; i++)
    {
		gint32 newlayer_ID = gimp_layer_copy (diffuse_ID);
		gfloat ok = (gfloat)(i + 1) * (gfloat)(i + 1);
		gimp_image_add_layer(image_ID, newlayer_ID, -1);
		gimp_image_set_active_layer(image_ID, newlayer_ID);
        
        /**
         * Filter "Gaussian Blur" applied
         * Standard plug-in. Source code ships with GIMP.
         * 
         * Add the ".0f" here to signify float in c language.
         */
        if (plug_in_gauss_connector(image_ID, newlayer_ID, ok * 3.0f, ok * 3.0f, 0) != 1) return;

        /**
         * Filter "Normalmap" applied
         * Non-Standard plug-in. Source code included.
         * 
         * original values:
		 * plug_in_normalmap_derby(image_ID, newlayer_ID, 5, 0.0, Depth * ok, 0, 0, 0, 0, 0, 0, 1, 0, 0.0, newlayer_ID)
         */
        nmapvals.filter = 5;
        nmapvals.minz = 0.0f;
        nmapvals.scale = Depth * ok;
        nmapvals.wrap = 0;
        nmapvals.height_source = 0;
        nmapvals.alpha = 0;
        nmapvals.conversion = 0;
        nmapvals.dudv = 0;
        nmapvals.xinvert = 0;
        nmapvals.yinvert = 1;
        nmapvals.swapRGB = 0;
        nmapvals.contrast = 0.0f;
        nmapvals.alphamap_id = newlayer_ID;
        normalmap(newlayer_ID, 0);
		
		if (i > 0)
        {
            /**
             * Originally removed by Omar Emad
             * 
			 * gimp_layer_set_opacity(newlayer,50-(i*10))
             */
             
			gimp_layer_set_mode(newlayer_ID, 5);
			gimp_image_merge_down(image_ID, newlayer_ID, 0);
			newlayer_ID = gimp_image_get_active_layer(image_ID);

            /**
             * Filter "Normalmap" applied
             * Non-Standard plug-in. Source code included.
             * 
             * original values:
             * plug_in_normalmap_derby(image_ID, newlayer_ID, 0, 0.0, 1.0, 0, 0, 0, 8, 0, 0, 0, 0, 0.0, newlayer_ID)
             */
            nmapvals.filter = 0;
            nmapvals.minz = 0.0f;
            nmapvals.scale = 1.0f;
            nmapvals.wrap = 0;
            nmapvals.height_source = 0;
            nmapvals.alpha = 0;
            nmapvals.conversion = 8;
            nmapvals.dudv = 0;
            nmapvals.xinvert = 0;
            nmapvals.yinvert = 0;
            nmapvals.swapRGB = 0;
            nmapvals.contrast = 0.0f;
            nmapvals.alphamap_id = newlayer_ID;
            normalmap(newlayer_ID, 0);
        }
    }
    
    /**
     * Removed by Derby Russell
     * Not Used any where and no
     * modifications are being made.
	 * drawable = gimp_image_get_active_layer(image_ID)
     */
    
    /**
     * Originally removed by Omar Emad
     * 
     *  newlayer=gimp_layer_copy (drawable, 1)
     *  gimp_image_add_layer(image,newlayer,-1)
     *  gimp_image_set_active_layer(image,newlayer)
     *  gimp_levels_stretch(newlayer)
     *  gimp_layer_set_opacity(newlayer,100)
     *  gimp_layer_set_mode(newlayer,5)
     *  gimp_image_merge_down(image,newlayer,0)		 
     */
}		

/**
 * The run function for Insanemap
 * 
 * @param img_ID         - gint32 image id of image to process with Insanemap.
 * 
 * imapvals provides all these parameters:
 * @param RemoveLighting - gint32 BOOL TRUE OR FALSE to remove lighting.
 * @param Resizie        - gint32 BOOL TRUE OR FALSE to resize image with a multiple of newWidth Integer.
 * @param Tile           - gint32 Tile images BOOL TRUE OR FALSE.
 * @param newWidth       - gint32 if Resizie is TRUE this value will increase both the width and height by this factor.
 * @param EdgeSpecular   - gint32 Edge Enhancing Specular BOOL TRUE OR FALSE.
 * @param defSpecular    - gint32 Specular Definition (0-255)
 * @param Depth          - gfloat Depth(+/-)
 * @param LargeDetails   - gint32 Large Detail Size (~3).
 * @param MediumDetails  - gint32 Medium Detail Intensity(%)
 * @param SmallDetails   - gint32 Small Detail Intensity(%)
 * @param ShapeRecog     - gint32 Shape Recognition(%)
 * @param smoothstep     - gint32 Smooth Step BOOL TRUE OR FALSE
 * @param invh           - gint32 Invert Height Map BOOL TRUE OR FALSE
 * @param ao             - gint32 ao
 * @param prev           - gint32 Preview BOOL TRUE OR FALSE
 */
gint32 batchnr(gint32 img_ID, gboolean preview_mode)
{
	gchar *file_name = gimp_image_get_filename(img_ID);
	gint32 image_ID = img_ID;
	gint size = gimp_image_width(image_ID);
	gfloat wsize = 0.0f;
	gfloat hsize = 0.0f;
    gint32 diffuse_ID = 0;
    gint32 normalmap_ID = 0;
    GString *file_name_temp = NULL;
    gint32 drawable_ID = 0;
    gint32 nResult = 0;
    
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.0);
    gtk_label_set_text(GTK_LABEL(progress_label), "Begin");

	if(imapvals.Resizie)
    {
        /**
         * Originally removed by Omar Emad
         * 
		 * upScale(getImgPath(),file_name,newWidth,size)
         */

		gboolean hiresimg = gimp_image_resize(image_ID, (gint)(imapvals.newWidth * size), (gint)(imapvals.newWidth * size), 0, 0);
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.01);
        gtk_label_set_text(GTK_LABEL(progress_label), "Resizing");

        /**
         * Since hiresimg is boolean and not an image id,
         * I am using it here as a double check.
         * I know this is not what was intended.
         * 
         * See below.
         */
        if (hiresimg)
        {
            /**
             * Originally removed by Omar Emad
             * 
             * hiresimg = gimp_file_load( getFilename(file_name,"_hd"), file_name)
             */

            /**
             * I believe this was an error.  hiresimg is a boolean value.
             * It looks as if it is being used as an image id.  gimp_image_resize causes the given
             * image id to be resized.  So, just using image_ID here is all that is needed after
             * the resize.  I am changing this code to do just that.
             * - Derby Russell
             * 
             * Old code:
             * gint32 drawable_ID = gimp_image_get_active_layer(hiresimg)
             */
            drawable_ID = gimp_image_get_active_layer(image_ID);
            gint32 noiselayer_ID = gimp_layer_copy (drawable_ID);
            gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.02);
            /**
             * Old code:
             * gimp_image_add_layer(hiresimg, noiselayer, -1)
             * gimp_image_set_active_layer(hiresimg, noiselayer)
             * plug_in_rgb_noise(hiresimg, noiselayer, 1, 1, 0.20, 0.20, 0.20, 0)
             */
            gimp_image_add_layer(image_ID, noiselayer_ID, -1);
            gimp_image_set_active_layer(image_ID, noiselayer_ID);
            gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.03);

            /**
             * Filter "RGB Noise" applied
             * Standard plug-in. Source code ships with GIMP.
             * 
             * Add the "f" here to signify float in c language.
             */
            gtk_label_set_text(GTK_LABEL(progress_label), "Noise");
            if (plug_in_rgb_noise_connector(image_ID, noiselayer_ID, 1, 1, 0.20f, 0.20f, 0.20f, 0.0f) != 1) return 0;
            gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.04);
            
            /**
             * Originally removed by Omar Emad
             * 
             * pdb.plug_in_blur(hiresimg,noiselayer)
             */
            
            gimp_layer_set_mode(noiselayer_ID, 14);
            
            /**
             * Old code:
             * gimp_image_merge_down(hiresimg, noiselayer, 0)
             */
            gimp_image_merge_down(image_ID, noiselayer_ID, 0);

            /**
             * Old code:
             * image = hiresimg
             * 
             * As I suspected.  This line of code was needed due
             * to the possible error above.  I am removing
             * this line and the error should be resolved.
             * - Derby Russell
             */
             
            /**
             * This next line is not needed due to the fact
             * that the line after that is commented out.
             * I am commenting out this line now.
             * - Derby Russell
             * 
             * drawable_ID = gimp_image_get_active_layer(image_ID);
             */

            /**
             * Originally removed by Omar Emad
             * 
             * ###########################analyze(drawable)
             */
        }
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(progress_label), "Stretch");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.04);
    }
         
	if(imapvals.RemoveLighting)
    {
        gtk_label_set_text(GTK_LABEL(progress_label), "Remove Shading");
		removeShading(image_ID);
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.05);
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(progress_label), "Stretch");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.05);
    }
		
	diffuse_ID = gimp_image_get_active_layer(image_ID);
	gimp_levels_stretch(diffuse_ID);
    file_name_temp = getFilename(file_name, "_d");
	if(imapvals.Tile)
    {
        /**
         * Filter "Tile Seamless" applied
         * Standard plug-in. Source code ships with GIMP.
         */
        gtk_label_set_text(GTK_LABEL(progress_label), "Making Seamless");
		if (plug_in_make_seamless_connector(image_ID, diffuse_ID) != 1) return 0;
        set_progress_label_as_file(file_name_temp, "_d");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.07);
    }
    else
    {
        set_progress_label_as_file(file_name_temp, "_d");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.07);
    }
    
	gimp_file_save(GIMP_RUN_NONINTERACTIVE, image_ID, diffuse_ID, file_name_temp->str, file_name_temp->str);
    g_string_free(file_name_temp, TRUE);
    file_name_temp = NULL;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.1);
	
    /**
     * Originally removed by Omar Emad
     * 
	 * drawable = gimp_image_get_active_layer(image)
	 * gimp_levels(drawable,0,64,128,1,0,255)
     */

	wsize = (gfloat)gimp_image_width(image_ID);
	hsize = (gfloat)gimp_image_width(image_ID);
    gtk_label_set_text(GTK_LABEL(progress_label), "Smoothing");
	blur(image_ID, diffuse_ID, wsize, hsize, imapvals.LargeDetails, 0);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.15);

    file_name_temp = getFilename(file_name, "_h");
	normalmap_ID = gimp_image_get_active_layer(image_ID);
	if(imapvals.smoothstep)
    {
        /**
         * Filter "Blur" applied
         * Standard plug-in. Source code ships with GIMP.
         */
        gtk_label_set_text(GTK_LABEL(progress_label), "Smoothing");
		if (plug_in_blur_connector(image_ID, normalmap_ID) != 1) return 0;
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.20);
    }
    else
    {
        set_progress_label_as_file(file_name_temp, "_h");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.20);
    }
	if(imapvals.invh)
    {
        /**
         * Colors Menu->Invert
         * Standard plug-in. Source code ships with GIMP.
         */
        if (plug_in_vinvert_connector(image_ID, normalmap_ID) != 1) return 0;
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.25);
    }
    else
    {
        set_progress_label_as_file(file_name_temp, "_h");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.25);
    }
		
	gimp_file_save(GIMP_RUN_NONINTERACTIVE, image_ID, normalmap_ID, file_name_temp->str, file_name_temp->str);
    g_string_free(file_name_temp, TRUE);
    file_name_temp = NULL;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.30);
	
    /**
     * Originally removed by Omar Emad
     * 
	 * lfnormal=gimp_layer_copy (diffuse, 1)
	 * gimp_image_add_layer(image,lfnormal,-1)
	 * gimp_image_raise_layer_to_top(image,lfnormal)
	 * pdb.plug_in_normalmap_derby(image, lfnormal,8,0.0,Depth,0,0,0,0,0,0,0,0,0.0,normalmap)
	 * blur(image,lfnormal,LargeDetails,1)
	 * normalmap = gimp_image_get_active_layer(image)
     */
    
    gtk_label_set_text(GTK_LABEL(progress_label), "Base Mapping");
    doBaseMap(image_ID, diffuse_ID, imapvals.Depth, imapvals.LargeDetails);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.35);
	normalmap_ID = gimp_image_get_active_layer(image_ID);
    
    file_name_temp = getFilename(file_name, "_ln");
    set_progress_label_as_file(file_name_temp, "_ln");
	gimp_file_save(GIMP_RUN_NONINTERACTIVE, image_ID, normalmap_ID, file_name_temp->str, file_name_temp->str);
    g_string_free(file_name_temp, TRUE);
    file_name_temp = NULL;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.40);

    file_name_temp = getFilename(file_name, "_sn");
	shapeRecognise(image_ID, normalmap_ID, imapvals.ShapeRecog);
	if(imapvals.smoothstep)
    {
		normalmap_ID = gimp_image_get_active_layer(image_ID);
        
        /**
         * Filter "Blur" applied
         * Standard plug-in. Source code ships with GIMP.
         */
        gtk_label_set_text(GTK_LABEL(progress_label), "Smoothing");
		if (plug_in_blur_connector(image_ID, normalmap_ID) != 1) return 0;
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.45);
    }
    else
    {
        set_progress_label_as_file(file_name_temp, "_sn");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.45);
    }

	saveLastOperation(image_ID, file_name_temp);
    g_string_free(file_name_temp, TRUE);
    file_name_temp = NULL;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.50);
	
    gtk_label_set_text(GTK_LABEL(progress_label), "Sharpen");
	sharpen(image_ID, diffuse_ID, imapvals.Depth, 0, imapvals.SmallDetails);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.55);
	normalmap_ID = gimp_image_get_active_layer(image_ID);

    /**
     * Filter Enhance "Sharpen" applied
     * Standard plug-in. Source code ships with GIMP.
     */
    gtk_label_set_text(GTK_LABEL(progress_label), "Sharpen more");
	if (plug_in_sharpen_connector(image_ID, normalmap_ID, 20) != 1) return 0;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.60);

    file_name_temp = getFilename(file_name, "_hn");
    set_progress_label_as_file(file_name_temp, "_hn");
	saveLastOperation(image_ID, file_name_temp);
    g_string_free(file_name_temp, TRUE);
    file_name_temp = NULL;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.65);
					
    gtk_label_set_text(GTK_LABEL(progress_label), "Sharpen again");
	sharpen(image_ID, diffuse_ID, imapvals.Depth, 6, imapvals.MediumDetails);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.70);
	normalmap_ID = gimp_image_get_active_layer(image_ID);
    
    /**
     * Filter "Blur" applied
     * Standard plug-in. Source code ships with GIMP.
     */
    gtk_label_set_text(GTK_LABEL(progress_label), "Smoothing");
	if (plug_in_blur_connector(image_ID, normalmap_ID) != 1) return 0;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.75);

    file_name_temp = getFilename(file_name, "_mn");
    set_progress_label_as_file(file_name_temp, "_mn");
	saveLastOperation(image_ID, file_name_temp);
    g_string_free(file_name_temp, TRUE);
    file_name_temp = NULL;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.78);
	
	gimp_drawable_set_visible(diffuse_ID, 0);
	gimp_image_merge_visible_layers(image_ID, 0);
	
	drawable_ID = gimp_image_get_active_layer(image_ID);
    
    /**
     * Filter "Normalmap" applied
     * Non-Standard plug-in. Source code included.
     * 
     * original values:
	 * plug_in_normalmap_derby(image, drawable, 0, 0.0, 1.0, 0, 0, 0, 8, 0, 0, 0, 0, 0.0, drawable)
     */
    nmapvals.filter = 0;
    nmapvals.minz = 0.0f;
    nmapvals.scale = 1.0f;
    nmapvals.wrap = 0;
    nmapvals.height_source = 0;
    nmapvals.alpha = 0;
    nmapvals.conversion = 8;
    nmapvals.dudv = 0;
    nmapvals.xinvert = 0;
    nmapvals.yinvert = 0;
    nmapvals.swapRGB = 0;
    nmapvals.contrast = 0.0f;
    nmapvals.alphamap_id = drawable_ID;
    gtk_label_set_text(GTK_LABEL(progress_label), "Normal map");
    normalmap(drawable_ID, 0);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.80);

    file_name_temp = getFilename(file_name, "_n");
    set_progress_label_as_file(file_name_temp, "_n");
	gimp_file_save(GIMP_RUN_NONINTERACTIVE, image_ID, drawable_ID, file_name_temp->str, file_name_temp->str);
    g_string_free(file_name_temp, TRUE);
    file_name_temp = NULL;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.85);

    /**
     * Colors ->  Components -> "Channel Mixer" applied
     * Standard plug-in. Source code ships with GIMP.
     * 
     * Add the "f" here to signify float in c language.
     * Removed 0.0 on first param and changed to 0 because boolean.
     */
    gtk_label_set_text(GTK_LABEL(progress_label), "Mixing Colors");
    if (plug_in_colors_channel_mixer_connector(image_ID, drawable_ID, 0, -200.0f, 0.0f, 0.0f, 0.0f, -200.0f, 0.0f, 0.0f, 0.0f, 1.0f) != 1) return 0;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.87);
    
	gimp_desaturate(drawable_ID);
	gimp_levels_stretch(drawable_ID);
    file_name_temp = getFilename(file_name, "_a");
    set_progress_label_as_file(file_name_temp, "_a");
	gimp_file_save(GIMP_RUN_NONINTERACTIVE, image_ID, drawable_ID, file_name_temp->str, file_name_temp->str);
    g_string_free(file_name_temp, TRUE);
    file_name_temp = NULL;
	gimp_drawable_set_visible(diffuse_ID, 1);
	gimp_image_set_active_layer(image_ID, diffuse_ID);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.90);
	
	if(imapvals.EdgeSpecular)
    {
        gtk_label_set_text(GTK_LABEL(progress_label), "Specular Edging");
		nResult = specularEdge(image_ID, file_name, imapvals.defSpecular);
        gtk_label_set_text(GTK_LABEL(progress_label), "Idle...");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 1.0);
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(progress_label), "Specular Smoothing");
		nResult = specularSmooth(image_ID, file_name, imapvals.defSpecular);
        gtk_label_set_text(GTK_LABEL(progress_label), "Idle...");
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 1.0);
    }
    
    return nResult;
}

