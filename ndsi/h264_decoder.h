#ifndef H264_DECODER_H_
#define H264_DECODER_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>

namespace serenegiant {
namespace media {

typedef enum COLOR_FORMAT {
	COLOR_FORMAT_YUV420 = 0,
	COLOR_FORMAT_RGB565LE,
	COLOR_FORMAT_BGR32,
} color_format_t;

class H264Decoder {
private:
	enum AVPixelFormat color_format;
	struct AVCodec *codec;
	struct AVCodecContext *codec_context;
	struct AVFrame *src;
	struct AVFrame *dst;
	struct SwsContext *sws_context;
	volatile bool frame_ready;
protected:
public:
	H264Decoder(const color_format_t &color_format = COLOR_FORMAT_YUV420);
	virtual ~H264Decoder();

	inline const bool is_frame_ready() const { return frame_ready; };
	inline const int width() { return codec_context ? codec_context->width : 0; };
	inline const int height() { return codec_context ? codec_context->height : 0; };
	inline const size_t get_output_bytes() { return avpicture_get_size(color_format, width(), height()); };
	int set_input_buffer(uint8_t *nal_units, const size_t &bytes, const int64_t &presentation_time_us);
	int get_output_buffer(uint8_t *buf, const size_t &capacity, int64_t &result_pts);
};

}	// namespace media
}	// namespace serenegiant

#endif /* H264_DECODER_H_ */
