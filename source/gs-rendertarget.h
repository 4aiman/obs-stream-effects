/*
 * Modern effects for a modern Streamer
 * Copyright (C) 2017 Michael Fabian Dirks
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#pragma once
#include <inttypes.h>
#include <memory>
#include "gs-texture.h"
extern "C" {
	#pragma warning( push )
	#pragma warning( disable: 4201 )
	#include <libobs/graphics/graphics.h>
	#pragma warning( pop )
}

namespace gs {
	class rendertarget {
		friend class rendertarget_op;

		public:
		rendertarget(gs_color_format colorFormat, gs_zstencil_format zsFormat);
		virtual ~rendertarget();

		gs_texture_t* get_object();
		void get_texture(gs::texture& tex);
		void get_texture(std::shared_ptr<gs::texture>& tex);
		void get_texture(std::unique_ptr<gs::texture>& tex);
		gs::rendertarget_op render(uint32_t width, uint32_t height);

		protected:
		gs_texrender_t* m_renderTarget;
		bool m_isBeingRendered;
	};

	class rendertarget_op {
		public:
		rendertarget_op(gs::rendertarget* rt, uint32_t width, uint32_t height);
		virtual ~rendertarget_op();

		// Move Constructor
		rendertarget_op(gs::rendertarget_op&&);

		// Copy Constructor
		rendertarget_op(const gs::rendertarget_op&) = delete;
		rendertarget_op& operator=(const gs::rendertarget_op& r) = delete;

		protected:
		gs::rendertarget* m_renderTarget;
	};
}
