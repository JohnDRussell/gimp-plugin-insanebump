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
 
#include "InsaneBumpDialog.h"
#include "scale.h"
 
static GtkWidget *dialog = NULL;
GtkWidget *preview = NULL;
GtkWidget *progress = NULL;
GtkWidget *progress_label = NULL;
static int update_preview = 0;
gint runme = 0;
static gint dialog_is_init = 0 ;

#define PREVIEW_SIZE 150
 
static void do_cleanup(gpointer data)
{
   gtk_main_quit();
}

static gint idle_callback(gpointer data)
{
   if(update_preview)
   {
       update_preview = 0 ;
   }
   return(1);
}

static void new_width_changed(GtkWidget *widget, gpointer data)
{
   imapvals.newWidth = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
   update_preview = 1;
}

static void def_specular_changed(GtkWidget *widget, gpointer data)
{
   imapvals.defSpecular = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
   update_preview = 1;
}

static void depth_changed(GtkWidget *widget, gpointer data)
{
   imapvals.Depth = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
   update_preview = 1;
}

static void large_detail_size_changed(GtkWidget *widget, gpointer data)
{
   imapvals.LargeDetails = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
   update_preview = 1;
}

static void medium_detail_intensity_changed(GtkWidget *widget, gpointer data)
{
   imapvals.MediumDetails = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
   update_preview = 1;
}

static void small_detail_intensity_changed(GtkWidget *widget, gpointer data)
{
   imapvals.SmallDetails = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
   update_preview = 1;
}

static void shape_recognition_changed(GtkWidget *widget, gpointer data)
{
   imapvals.ShapeRecog = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
   update_preview = 1;
}

static void ao_changed(GtkWidget *widget, gpointer data)
{
   imapvals.ao = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
   update_preview = 1;
}

static void remlightbtn_clicked(GtkWidget *widget, gpointer data)
{
    if (!dialog_is_init) return;
    if (imapvals.RemoveLighting == 0)
    {
        imapvals.RemoveLighting = 1;
        gtk_button_set_label(GTK_BUTTON(widget), "Yes");
    }
    else
    {
        imapvals.RemoveLighting = 0;
        gtk_button_set_label(GTK_BUTTON(widget), "No");
    }
    update_preview = 1;
}

static void upscale_HD_clicked(GtkWidget *widget, gpointer data)
{
    if (!dialog_is_init) return;
    if (imapvals.Resizie == 0)
    {
        imapvals.Resizie = 1;
        gtk_button_set_label(GTK_BUTTON(widget), "Yes");
    }
    else
    {
        imapvals.Resizie = 0;
        gtk_button_set_label(GTK_BUTTON(widget), "No");
    }
    update_preview = 1;
}

static void tile_clicked(GtkWidget *widget, gpointer data)
{
    if (!dialog_is_init) return;
    if (imapvals.Tile == 0)
    {
        imapvals.Tile = 1;
        gtk_button_set_label(GTK_BUTTON(widget), "Yes");
    }
    else
    {
        imapvals.Tile = 0;
        gtk_button_set_label(GTK_BUTTON(widget), "No");
    }
    update_preview = 1;
}

static void edge_enhaning_specular_clicked(GtkWidget *widget, gpointer data)
{
    if (!dialog_is_init) return;
    if (imapvals.EdgeSpecular == 0)
    {
        imapvals.EdgeSpecular = 1;
        gtk_button_set_label(GTK_BUTTON(widget), "Yes");
    }
    else
    {
        imapvals.EdgeSpecular = 0;
        gtk_button_set_label(GTK_BUTTON(widget), "No");
    }
    update_preview = 1;
}

static void smooth_step_clicked(GtkWidget *widget, gpointer data)
{
    if (!dialog_is_init) return;
    if (imapvals.smoothstep == 0)
    {
        imapvals.smoothstep = 1;
        gtk_button_set_label(GTK_BUTTON(widget), "Yes");
    }
    else
    {
        imapvals.smoothstep = 0;
        gtk_button_set_label(GTK_BUTTON(widget), "No");
    }
    update_preview = 1;
}

static void invert_height_map_clicked(GtkWidget *widget, gpointer data)
{
    if (!dialog_is_init) return;
    if (imapvals.invh == 0)
    {
        imapvals.invh = 1;
        gtk_button_set_label(GTK_BUTTON(widget), "Yes");
    }
    else
    {
        imapvals.invh = 0;
        gtk_button_set_label(GTK_BUTTON(widget), "No");
    }
    update_preview = 1;
}

/** Commenting out the preview area for the first release. */
//static void preview_clicked(GtkWidget *widget, gpointer data)
//{
//    /** Commenting out all references to preview for first release. */
//    // GimpDrawable *drawable;
//    
//    if (!dialog_is_init) return;
//    if (imapvals.prev == 0)
//    {
//        imapvals.prev = 1;
//        // gtk_button_set_label(GTK_BUTTON(widget), "Yes");
//    }
//    else
//    {
//        imapvals.prev = 0;
//        // gtk_button_set_label(GTK_BUTTON(widget), "No");
//    }
//    
//    //    // if(!is_3D_preview_active())
//    //    // {
//    //       drawable = g_object_get_data(G_OBJECT(widget), "drawable");
//    //        if (imapvals.image_ID != 0)
//    //        {
//    //            update_preview = 0;
//    //            // batchnr(imapvals.image_ID);
//    //            // GimpDrawable* alphamap = gimp_drawable_get(imapvals.image_ID);
//    //            GimpPixelRgn amap_rgn;
//    //            gint pw, ph, rowbytes;
//    //            guchar *tmp = NULL;
//    //            guchar *dst = NULL;
//    //            /** DERBY REMOVED THIS */
//    //            /** DERBY REMOVED THIS */
//    //            /** DERBY REMOVED THIS */
//    //              // update_3D_preview(width, height, bpp, dst);
//    //            /** DERBY REMOVED THIS */
//    //            /** DERBY REMOVED THIS */
//    //            /** DERBY REMOVED THIS */
//    //
//    //            pw = GIMP_PREVIEW_AREA(preview)->width;
//    //            ph = GIMP_PREVIEW_AREA(preview)->height;
//    //            rowbytes = pw * drawable->bpp;
//    //
//    //            dst = g_malloc(pw * ph * drawable->bpp);
//    //            if(dst == 0)
//    //            {
//    //                g_message("Memory allocation error!");
//    //                return;
//    //            }
//    //
//    //
//    //            tmp = g_malloc(pw * ph * drawable->bpp);
//    //
//    //            gimp_pixel_rgn_init(&amap_rgn, drawable, 0, 0, drawable->width, drawable->height, 0, 0);
//    //            gimp_pixel_rgn_get_rect(&amap_rgn, tmp, 0, 0, drawable->width, drawable->height);
//    //
//    //            scale_pixels(tmp, pw, ph, dst, drawable->width, drawable->height, drawable->bpp);
//    //
//    //            gimp_preview_area_draw(GIMP_PREVIEW_AREA(preview), 0, 0, pw, ph,
//    //                                 (drawable->bpp == 4) ? GIMP_RGBA_IMAGE : GIMP_RGB_IMAGE,
//    //                                 tmp, rowbytes);
//    //
//    //            g_free(tmp);
//    //            g_free(dst);
//    //        }
//    //
//    //       // show_3D_preview(drawable);
//    //       update_preview = 1;
//    //    // }
//}

static void insanebump_dialog_response(GtkWidget *widget, gint response_id,
                                      gpointer data)
{
   switch(response_id)
   {
      case GTK_RESPONSE_OK:
         gimp_progress_init("Creating InsaneBump...");
         runme = 2;
         if (batchnr(imapvals.image_ID, 1) == 0)
         {
             runme = 1;
         }
         return;
      default:
         runme = 2;
         gtk_widget_destroy(widget);
         break;
   }
}

/**
 * To understand how to setup this function you must understand:
 * 
 * gimp_table_attach_aligned
 * 
 * To understand that you will find information in only one spot:
 * 
 * c:\gimp-2.6.11\libgimpwidgets\gimpwidgets.c on or about line number 1118
 * which states:
 * 
 **
 * gimp_table_attach_aligned:
 * @table:      The #GtkTable the widgets will be attached to.
 * @column:     The column to start with.
 * @row:        The row to attach the widgets.
 * @label_text: The text for the #GtkLabel which will be attached left of
 *              the widget.
 * @xalign:     The horizontal alignment of the #GtkLabel.
 * @yalign:     The vertival alignment of the #GtkLabel.
 * @widget:     The #GtkWidget to attach right of the label.
 * @colspan:    The number of columns the widget will use.
 * @left_align: %TRUE if the widget should be left-aligned.
 *
 * Note that the @label_text can be %NULL and that the widget will be
 * attached starting at (@column + 1) in this case, too.
 *
 * Returns: The created #GtkLabel.
 **
 * GtkWidget *
 * gimp_table_attach_aligned (GtkTable    *table,
 *                            gint         column,
 *                            gint         row,
 *                            const gchar *label_text,
 *                            gfloat       xalign,
 *                            gfloat       yalign,
 *                            GtkWidget   *widget,
 *                            gint         colspan,
 *                            gboolean     left_align);
 * 
 */
static void CreateToggleButton(GtkWidget *table, gint row, GCallback *function, const gchar *szName, gint32 nVal)
{
    GtkWidget *btn = NULL;
    if (nVal == 1)
    {
       btn = gtk_toggle_button_new_with_label("Yes");
    }
    else
    {
       btn = gtk_toggle_button_new_with_label("No");
    }
    if (btn != NULL)
    {
        gtk_signal_connect(GTK_OBJECT(btn), "clicked",
                          GTK_SIGNAL_FUNC(function), 0);
        gimp_table_attach_aligned(GTK_TABLE(table), 0, row, szName, 0, 0.5,
                                 btn, 1, 0);
        gtk_widget_show(btn);
        if (nVal == 1)
        {
           gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btn), TRUE);
        }
    }
}

/**
 * To understand how to setup this function you must understand:
 * 
 * gimp_table_attach_aligned
 * 
 * To understand that you will find information in only one spot:
 * 
 * c:\gimp-2.6.11\libgimpwidgets\gimpwidgets.c on or about line number 1118
 * which states:
 * 
 **
 * gimp_table_attach_aligned:
 * @table:      The #GtkTable the widgets will be attached to.
 * @column:     The column to start with.
 * @row:        The row to attach the widgets.
 * @label_text: The text for the #GtkLabel which will be attached left of
 *              the widget.
 * @xalign:     The horizontal alignment of the #GtkLabel.
 * @yalign:     The vertival alignment of the #GtkLabel.
 * @widget:     The #GtkWidget to attach right of the label.
 * @colspan:    The number of columns the widget will use.
 * @left_align: %TRUE if the widget should be left-aligned.
 *
 * Note that the @label_text can be %NULL and that the widget will be
 * attached starting at (@column + 1) in this case, too.
 *
 * Returns: The created #GtkLabel.
 **
 * GtkWidget *
 * gimp_table_attach_aligned (GtkTable    *table,
 *                            gint         column,
 *                            gint         row,
 *                            const gchar *label_text,
 *                            gfloat       xalign,
 *                            gfloat       yalign,
 *                            GtkWidget   *widget,
 *                            gint         colspan,
 *                            gboolean     left_align);
 * 
 */
static void CreateInteger255SpinButton(GtkWidget *table, gint row, GCallback *function, const gchar *szName, gint32 nVal, gint32 allow_neg)
{
   GtkObject *adj = NULL;
   GtkWidget *spin = NULL;
   if (allow_neg)
   {
       adj = gtk_adjustment_new((gdouble)nVal, -1000, 1000, 1, 10, 10);
   }
   else
   {
       adj = gtk_adjustment_new((gdouble)nVal, 0, 1000, 1, 10, 10);
   }
   spin = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 1, 0);
   gtk_widget_show(spin);
   gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(spin), GTK_UPDATE_IF_VALID);
   gtk_signal_connect(GTK_OBJECT(spin), "value_changed",
                      GTK_SIGNAL_FUNC(function), 0);
   gimp_table_attach_aligned(GTK_TABLE(table), 0, row, szName, 0, 0.5,
                             spin, 1, 0);
}

/**
 * table_attach_progress:
 * @table:      The #GtkTable the widgets will be attached to.
 * @column:     The column to start with.
 * @row:        The row to attach the widgets.
 * @label_text: The text for the #GtkLabel which will be attached left of
 *              the widget.
 * @xalign:     The horizontal alignment of the #GtkLabel.
 * @yalign:     The vertival alignment of the #GtkLabel.
 * @widget:     The #GtkWidget to attach right of the label.
 * @colspan:    The number of columns the widget will use.
 * @left_align: %TRUE if the widget should be left-aligned.
 *
 * Note that the @label_text can be %NULL and that the widget will be
 * attached starting at (@column + 1) in this case, too.
 *
 * Returns: The created #GtkLabel.
 **/
void table_attach_progress(GtkTable    *table,
                                 gint         column,
                                 gint         row,
                                 const gchar *label_text,
                                 gfloat       xalign,
                                 gfloat       yalign,
                                 GtkWidget   *widget,
                                 gint         colspan,
                                 gboolean     left_align)
{
    if (label_text)
    {
        progress_label = gtk_label_new_with_mnemonic (label_text);
        gtk_misc_set_alignment (GTK_MISC (progress_label), xalign, yalign);
        gtk_label_set_justify (GTK_LABEL (progress_label), GTK_JUSTIFY_LEFT);
        gtk_table_attach (table, progress_label,
                          column, column + 1,
                          row, row + 1,
                          GTK_FILL, GTK_FILL, 0, 0);
        gtk_widget_show (progress_label);
    }

    if (left_align)
    {
        GtkWidget *hbox = gtk_hbox_new (FALSE, 0);

        gtk_box_pack_start (GTK_BOX (hbox), widget, FALSE, FALSE, 0);
        gtk_widget_show (widget);

        widget = hbox;
    }

    gtk_table_attach (table, widget,
                      column, column + 1 + colspan + 1,
                      row + 1, row + 2,
                      GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);

    gtk_widget_show (widget);
}
  
gint InsaneBumpDialog(GimpDrawable *drawable, const gchar *szBinary)
{
   GtkWidget *hbox;
   /** Commenting out the preview area for the first release*/
   // GtkWidget *hbox, *vbox, *abox;
   // GtkWidget *btn;
   GtkWidget *table;
   // GtkWidget *frame;

   gimp_ui_init(szBinary, TRUE);
      
   dialog = gimp_dialog_new("Insane Bump", szBinary,
                            0, 0, gimp_standard_help_func, 0,
                            GTK_STOCK_CLOSE, GTK_RESPONSE_CANCEL,
                            GTK_STOCK_EXECUTE, GTK_RESPONSE_OK,
                            NULL);

   gtk_signal_connect(GTK_OBJECT(dialog), "response",
                      GTK_SIGNAL_FUNC(insanebump_dialog_response),
                      0);
   gtk_signal_connect(GTK_OBJECT(dialog), "destroy",
                      GTK_SIGNAL_FUNC(do_cleanup),
                      0);

   hbox = gtk_hbox_new(0, 8);
   gtk_container_set_border_width(GTK_CONTAINER(hbox), 8);
   gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),hbox, 1, 1, 0);
   gtk_widget_show(hbox);

    /** Commenting out the preview area for the first release. */   
    //   /**
    //    * Create the Preview area.
    //    */
    //   
    //   vbox = gtk_vbox_new(0, 8);
    //   gtk_box_pack_start(GTK_BOX(hbox), vbox, 1, 1, 0);
    //   gtk_widget_show(vbox);
    //   
    //   frame = gtk_frame_new("Preview");
    //   gtk_box_pack_start(GTK_BOX(vbox), frame, 0, 0, 0);
    //   gtk_widget_show(frame);
    //   
    //   abox = gtk_alignment_new(0.5, 0.5, 0.0, 0.0);
    //   gtk_container_set_border_width(GTK_CONTAINER (abox), 4);
    //   gtk_container_add(GTK_CONTAINER(frame), abox);
    //   gtk_widget_show(abox);
    //
    //   frame = gtk_frame_new(NULL);
    //   gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
    //   gtk_container_add(GTK_CONTAINER(abox), frame);
    //   gtk_widget_show(frame);
    //
    //   preview = gimp_preview_area_new();
    //   gimp_preview_area_set_max_size(GIMP_PREVIEW_AREA(preview), PREVIEW_SIZE, PREVIEW_SIZE);
    //   gtk_drawing_area_size(GTK_DRAWING_AREA(preview), PREVIEW_SIZE, PREVIEW_SIZE);
    //   gtk_container_add(GTK_CONTAINER(frame), preview);
    //   gtk_widget_show(preview);
    //   
    //   btn = gtk_button_new_with_label("3D Preview");
    //   gtk_signal_connect(GTK_OBJECT(btn), "clicked",
    //                      GTK_SIGNAL_FUNC(preview_clicked), 0);
    //
    //   g_object_set_data(G_OBJECT(btn), "drawable", drawable);
    //
    //   gtk_box_pack_start(GTK_BOX(vbox), btn, 0, 0, 0);
    //   gtk_widget_show(btn);

   /**
    * Create a table to place all the right hand items into.
    * Really could just be a horizontal box with all packed into.
    * Copied other persons code.
    */
   table = gtk_table_new(17, 1, 0);
   gtk_widget_show(table);
   gtk_box_pack_start(GTK_BOX(hbox), table, 1, 1, 0);
   gtk_table_set_row_spacings(GTK_TABLE(table), 8);
   gtk_table_set_col_spacings(GTK_TABLE(table), 8);

   /**
    * Remove Lighting
    * [         No           ]
    * button
    */
   CreateToggleButton(table, 1, (GCallback *)&remlightbtn_clicked, "Remove Lighting", imapvals.RemoveLighting);
   
   /**
    * Upscale(HD)
    * [         No           ]
    * button
    */
   CreateToggleButton(table, 2, (GCallback *)&upscale_HD_clicked, "Upscale(HD)", imapvals.Resizie);

   /**
    * Tile
    * [*********Yes***********]
    * button
    */
   CreateToggleButton(table, 3, (GCallback *)&tile_clicked, "Tile", imapvals.Tile);

   /**
    * New Width(Integer Times larger)
    * [2                     ][^][v]
    * edit control with spinner arrows at end of control
    */
   CreateInteger255SpinButton(table, 4, (GCallback *)&new_width_changed, "New Width(Integer Times larger)", imapvals.newWidth, 0);

   /**
    * Edge Enhaning Specular
    * [*********Yes***********]
    * button
    */
   CreateToggleButton(table, 5, (GCallback *)&edge_enhaning_specular_clicked, "Edge Enhaning Specular", imapvals.EdgeSpecular);

   /**
    * Specular Definition(0-255)
    * [64                     ][^][v]
    * edit control with spinner arrows at end of control
    */
   CreateInteger255SpinButton(table, 6, (GCallback *)&def_specular_changed, "Specular Definition(0-255)", imapvals.defSpecular, 0);

   /**
    * Depth(+/-)
    * [20                     ][^][v]
    * edit control with spinner arrows at end of control
    */
   CreateInteger255SpinButton(table, 7, (GCallback *)&depth_changed, "Depth(+/-)", imapvals.Depth, 1);

   /**
    * Large Detail Size
    * [3                      ][^][v]
    * edit control with spinner arrows at end of control
    */
   CreateInteger255SpinButton(table, 8, (GCallback *)&large_detail_size_changed, "Large Detail Size", imapvals.LargeDetails, 0);

   /**
    * Medium Detail Intensity(%)
    * [50                     ][^][v]
    * edit control with spinner arrows at end of control
    */
   CreateInteger255SpinButton(table, 9, (GCallback *)&medium_detail_intensity_changed, "Medium Detail Intensity(%)", imapvals.MediumDetails, 0);

   /**
    * Small Detail Intensity(%)
    * [50                     ][^][v]
    * edit control with spinner arrows at end of control
    */
   CreateInteger255SpinButton(table, 10, (GCallback *)&small_detail_intensity_changed, "Small Detail Intensity(%)", imapvals.SmallDetails, 0);

   /**
    * Shape Recognition(%)
    * [50                     ][^][v]
    * edit control with spinner arrows at end of control
    */
   CreateInteger255SpinButton(table, 11, (GCallback *)&shape_recognition_changed, "Shape Recognition(%)", imapvals.ShapeRecog, 0);

   /**
    * Smooth Step
    * [*********Yes***********]
    * button
    */
   CreateToggleButton(table, 12, (GCallback *)&smooth_step_clicked, "Smooth Step", imapvals.smoothstep);

   /**
    * Invert Height Map
    * [         No           ]
    * button
    */
   CreateToggleButton(table, 13, (GCallback *)&invert_height_map_clicked, "Invert Height Map", imapvals.invh);

   /**
    * ao
    * [50                     ][^][v]
    * edit control with spinner arrows at end of control
    */
   CreateInteger255SpinButton(table, 14, (GCallback *)&ao_changed, "ao", imapvals.ao, 0);

    //   /**
    //    * Preview
    //    * [*********Yes***********]
    //    * button
    //    */
    //   CreateToggleButton(table, 15, (GCallback *)&preview_clicked, "Preview", imapvals.prev);
   
   progress = gtk_progress_bar_new();
   gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progress), 0.0);
   table_attach_progress(GTK_TABLE(table), 0, 16, "Idle...", 0, 0.5,
                         progress, 1, 0);
   gtk_widget_show(progress);
   
   gtk_widget_show(dialog);

   update_preview = 1;
   gtk_timeout_add(100, idle_callback, drawable);
   
   runme = 0;
   
   dialog_is_init = 1 ;
   
   gtk_main();
   
   return(runme);
}
