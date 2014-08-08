/*
 * XGL
 *
 * Copyright (C) 2014 LunarG, Inc.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef IMG_H
#define IMG_H

#include "kmd/winsys.h"
#include "intel.h"
#include "obj.h"

#define INTEL_IMG_MAX_LEVELS 16

/**
 * A 3D image slice, cube face, or array layer.
 */
struct intel_img_slice {
   /* 2D offset to the slice */
   unsigned x, y;
   unsigned flags;
};

struct intel_img {
    struct intel_obj obj;

    XGL_FORMAT bo_format;

    enum intel_tiling_mode tiling;
    unsigned long bo_stride; /* distance between two block rows in bytes */
    unsigned long bo_height;

    unsigned block_width;
    unsigned block_height;
    unsigned block_size;

    /* true if the mip level alignments are stricter */
    bool halign_8, valign_4;
    /* true if space is reserved between layers */
    bool array_spacing_full;
    /* true if samples are interleaved */
    bool interleaved;

    struct intel_img_slice *slices[INTEL_IMG_MAX_LEVELS];
};

static inline struct intel_img *intel_img(XGL_IMAGE image)
{
    return (struct intel_img *) image;
}

static inline struct intel_img *intel_img_from_base(struct intel_base *base)
{
    return (struct intel_img *) base;
}

static inline struct intel_img *intel_img_from_obj(struct intel_obj *obj)
{
    return intel_img_from_base(&obj->base);
}

XGL_RESULT intel_img_create(struct intel_dev *dev,
                            const XGL_IMAGE_CREATE_INFO *info,
                            struct intel_img **img_ret);

void intel_img_destroy(struct intel_img *img);

XGL_RESULT XGLAPI intelCreateImage(
    XGL_DEVICE                                  device,
    const XGL_IMAGE_CREATE_INFO*                pCreateInfo,
    XGL_IMAGE*                                  pImage);

XGL_RESULT XGLAPI intelGetImageSubresourceInfo(
    XGL_IMAGE                                   image,
    const XGL_IMAGE_SUBRESOURCE*                pSubresource,
    XGL_SUBRESOURCE_INFO_TYPE                   infoType,
    XGL_SIZE*                                   pDataSize,
    XGL_VOID*                                   pData);

#endif /* IMG_H */
