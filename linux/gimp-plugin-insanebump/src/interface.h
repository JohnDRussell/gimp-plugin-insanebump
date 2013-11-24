/* GIMP Plug-in InsaneBump
 * Copyright (C) 2013  Derby Russsell <jdrussell51@gmail.com> (the "Author").
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Author of the
 * Software shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization from the Author.
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

/*  Constants  */

#define PREVIEW_SIZE 150
#define PREVIEW_RGB_SIZE 67500
#define PREVIEW_RGBA_SIZE 90000

/* structures */

typedef struct
{
    GimpDrawable *drawable_d;
    GtkWidget *preview_d;
    GimpDrawable *drawable_ao;
    GtkWidget *preview_ao;
    GimpDrawable *drawable_s;
    GtkWidget *preview_s;
    GimpDrawable *drawable_p;
    GtkWidget *preview_p;
    GimpDrawable *drawable_n;
    GtkWidget *preview_n;
} PreviewDraws;

/*  Global variables  */

extern gchar _active;
extern PlugInVals local_vals;
extern int update_preview;
extern gint dialog_is_init;
extern PreviewDraws pDrawables;

/*  Public functions  */

void init_drawables(void);
int is_3D_preview_active(void);
gint InsaneBumpDialog(GimpDrawable *drawable,
                      const gchar *szBinary,
                      PlugInVals *vals);
void CreateLeftPreviewFrames(GtkWidget *hbox);
void CreateRightPreviewToggleButton(GtkWidget *hbox);
void preview_redraw(void);
void preview_clicked(GtkWidget *widget, gpointer data);
void preview_clicked_occlusion(GtkWidget *widget, gpointer data);
void preview_clicked_diffuse(GtkWidget *widget, gpointer data);
void preview_clicked_specular(GtkWidget *widget, gpointer data);
void preview_clicked_normal(GtkWidget *widget, gpointer data);

#endif /* __INTERFACE_H__ */
