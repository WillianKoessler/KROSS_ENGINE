#pragma once

namespace Kross {
    class RendererStats : public Resource
    {
		int plotsize = 128;
		bool pause_frame_plot_animation = false;
		const char* frame_plot_options[2] = { "Frames per Second", "Elapsed Time" };
		int plot_type = 0;
		size_t frame_count = 0;
		float FrameRate = 0;
		float framerate_buffer = 0;
		int rate_tick = 10;
		float* frames;
    public:
        RendererStats();
        ~RendererStats();

        void Show(double ts);
    };
}
