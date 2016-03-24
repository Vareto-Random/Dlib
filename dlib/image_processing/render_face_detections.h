// Copyright (C) 2014  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#ifndef DLIB_RENDER_FACE_DeTECTIONS_H_
#define DLIB_RENDER_FACE_DeTECTIONS_H_

#include "full_object_detection.h"
#include "../gui_widgets.h"
#include "render_face_detections_abstract.h"
#include <vector>

namespace dlib
{
    inline std::vector<image_window::overlay_line> render_face_detections (
        const std::vector<full_object_detection>& dets,
        const rgb_pixel color = rgb_pixel(0,255,0)
    )
    {
        std::vector<image_window::overlay_line> lines;
        for (unsigned long i = 0; i < dets.size(); ++i)
        {
            // DLIB_CASSERT(dets[i].num_parts() == 39,
            //     "\t std::vector<image_window::overlay_line> render_face_detections()"
            //     << "\n\t Invalid inputs were given to this function. "
            //     << "\n\t dets["<<i<<"].num_parts():  " << dets[i].num_parts() 
            // );

            const full_object_detection& d = dets[i];
            for (unsigned long i = 1; i <= 8; ++i) // face outline
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            for (unsigned long i = 10; i <= 13; ++i) // eyebrow
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            for (unsigned long i = 15; i <= 17; ++i) // noseTop
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
            
            for (unsigned long i = 18; i <= 20; ++i) // noseBottom
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            for (unsigned long i = 22; i <= 26; ++i) // eye
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
            lines.push_back(image_window::overlay_line(d.part(21), d.part(26), color));

            for (unsigned long i = 31; i <= 35; ++i) // outer mouth
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
            lines.push_back(image_window::overlay_line(d.part(35), d.part(27), color));

            //inner mouth
            lines.push_back(image_window::overlay_line(d.part(28), d.part(36), color));
            lines.push_back(image_window::overlay_line(d.part(36), d.part(38), color));
            lines.push_back(image_window::overlay_line(d.part(38), d.part(37), color));
            lines.push_back(image_window::overlay_line(d.part(37), d.part(29), color));

            // for (unsigned long i = 61; i <= 67; ++i)
            //     lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
            // lines.push_back(image_window::overlay_line(d.part(60), d.part(67), color));
        }
        return lines;
    }

// ----------------------------------------------------------------------------------------

    inline std::vector<image_window::overlay_line> render_face_detections (
        const full_object_detection& det,
        const rgb_pixel color = rgb_pixel(0,255,0)
    )
    {
        std::vector<full_object_detection> dets;
        dets.push_back(det);
        return render_face_detections(dets, color);
    }

// ----------------------------------------------------------------------------------------

}

#endif // DLIB_RENDER_FACE_DeTECTIONS_H_

