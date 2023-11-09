//----------------------------------------------------------------------------
// Copyright Persistant Studios, SARL. All Rights Reserved.
// https://www.popcornfx.com/terms-and-conditions/
//----------------------------------------------------------------------------

#include "PopcornFX_precompiled.h"
#include "AtomRenderDataFactory.h"

#if defined(O3DE_USE_PK)

#include "AtomRendererCache.h"

#include <pk_particles/include/ps_effect.h>

#include <Atom/RPI.Public/RPIUtils.h>
#include <Atom/RPI.Public/RPISystemInterface.h>
#include <Atom/RPI.Public/Scene.h>
#include <Atom/RHI.Reflect/InputStreamLayoutBuilder.h>
#include <AzCore/Console/ILogger.h>

#include "BillboardBatchDrawer.h"
#include "RibbonBatchDrawer.h"
#include "MeshBatchDrawer.h"
#include "LightBatchDrawer.h"

namespace PopcornFX {
//----------------------------------------------------------------------------

CRendererBatchDrawer	*CAtomRenderDataFactory::CreateBatchDrawer(ERendererClass rendererType, const PRendererCacheBase &rendererCache, bool gpuStorage)
{
	(void)rendererCache;
	if (!gpuStorage)
	{
		switch (rendererType)
		{
		case	Renderer_Billboard:
		{
			CBillboardBatchDrawer *batch = PK_NEW(CBillboardBatchDrawer);
			return batch;
		}
		case	Renderer_Ribbon:
		{
			CRibbonBatchDrawer *batch = PK_NEW(CRibbonBatchDrawer);
			return batch;
		}
		case	Renderer_Mesh:
		{
			CMeshBatchDrawer *batch = PK_NEW(CMeshBatchDrawer);
			return batch;
		}
		case	Renderer_Light:
		{
			CLightBatchDrawer *batch = PK_NEW(CLightBatchDrawer);
			return batch;
		}
		default:
			return null;
		}
	}
	else
	{
		PK_ASSERT_NOT_IMPLEMENTED_MESSAGE("PopcornFX GPU simulation is not implemented in O3DE yet...");
	}
	return null;
}

//----------------------------------------------------------------------------

PRendererCacheBase		CAtomRenderDataFactory::CreateRendererCache(const PRendererDataBase &renderer, const CParticleDescriptor *particleDesc)
{
	// This is called when the effect is preloaded, or when first instantiated
	// It is required that a renderer cache is created per renderer.

	// Returned value is PRendererCacheBase (strong ref), you can leave PopcornFX handle the cache's lifetime (no need to free it)
	// It will be destroyed when effect is unloaded.

	// We create the renderer cache here:
	PAtomRendererCache	rendererCache = PK_NEW(CAtomRendererCache);
	if (!PK_VERIFY(rendererCache != null))
	{
		AZ_Printf("PopcornFX", "Could not allocate the renderer cache(effect: '%s')", particleDesc->ParentEffect()->FilePath().Data());
		return null;
	}

	rendererCache->InitFromRenderer(*renderer, m_PackPath, particleDesc->ParentEffect()->FilePath());
	if (renderer->m_RendererType != Renderer_Light)
	{
		if (!PK_VERIFY(m_RendererLoader.AddMaterialToCreate(rendererCache)))
		{
			AZ_Printf("PopcornFX", "Could not add materials to create the render cache (effect: '%s')", particleDesc->ParentEffect()->FilePath().Data());
			return null;
		}
		if (rendererCache->m_RendererType == Renderer_Mesh)
		{
			if (!PK_VERIFY(m_RendererLoader.AddGeometryToCreate(rendererCache)))
			{
                AZ_Printf("PopcornFX", "Could not add geometry to create the render cache (effect: '%s')", particleDesc->ParentEffect()->FilePath().Data());
                return null;

			}
		}
	}
	return rendererCache;
}

//----------------------------------------------------------------------------
}

#endif //O3DE_USE_PK
