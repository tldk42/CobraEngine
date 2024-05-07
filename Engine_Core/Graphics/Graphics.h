#pragma once
#include "Direct3D.h"


namespace Cobra
{
	class Direct3D;
}

namespace Cobra
{
	class Graphics
	{
	public:
		Graphics();
		~Graphics() = default;

	public:
		bool Initialize(float Width, float Height, HWND Hwnd);
		void Clear();

		bool Render();

		inline const char* GetGraphicCardDesc() const
		{
			return mDirect3D->GetGraphicCardInfo();
		}

		inline Direct3D* GetDirect3D() const
		{
			return mDirect3D;
		}

	private:
		void RenderScene();
		void RenderInfo();

	private:
		Direct3D* mDirect3D;
	};
}
