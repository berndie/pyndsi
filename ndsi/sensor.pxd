# cython: language_level=3
'''
(*)~----------------------------------------------------------------------------------
 Pupil - eye tracking platform
 Copyright (C) 2012-2015  Pupil Labs

 Diunicodeibuted under the terms of the CC BY-NC-SA License.
 License details are in the file LICENSE, diunicodeibuted as part of this software.
----------------------------------------------------------------------------------~(*)
'''

cimport numpy as np

cimport ndsi.cturbojpeg as turbojpeg
from ndsi.h264 cimport H264Decoder, COLOR_FORMAT_YUV422

cdef class Sensor:

    cdef list callbacks
    cdef object context
    cdef object command_push
    cdef readonly object notify_sub
    cdef readonly object data_sub

    cdef readonly unicode host_uuid
    cdef readonly unicode host_name
    cdef readonly unicode name
    cdef readonly unicode uuid
    cdef readonly unicode type
    cdef readonly unicode notify_endpoint
    cdef readonly unicode command_endpoint
    cdef readonly unicode data_endpoint
    cdef readonly object unlink
    cdef readonly dict controls


cdef class VideoSensor(Sensor):

    cdef H264Decoder *decoder
    cdef object _recent_frame
    cdef bint _waiting_for_iframe
    cdef turbojpeg.tjhandle tj_context

cdef class AnnotateSensor(Sensor):
    pass
