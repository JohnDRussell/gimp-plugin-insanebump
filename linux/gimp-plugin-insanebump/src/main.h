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

#ifndef __MAIN_H__
#define __MAIN_H__

#define NAME_AND_VERSION "Insane Bump 1.0.4"

typedef struct
{
    gint32 RemoveLighting;
    gint32 Resizie;
    gint32 Tile;
    gint32 newWidth;
    gint32 EdgeSpecular;
    gint32 defSpecular;
    gfloat Depth;
    gint32 LargeDetails;
    gint32 MediumDetails;
    gint32 SmallDetails;
    gint32 ShapeRecog;
    gint32 smoothstep;
    gint32 Noise;
    gint32 invh;
    gint32 ao;
    gint32 image_ID;
    gint32 prev;
} PlugInVals;


/*  Default values  */

extern const PlugInVals default_vals;

void copyPlugInVals(const PlugInVals *some_vals_source, PlugInVals *some_vals_destination);

#endif /* __MAIN_H__ */
