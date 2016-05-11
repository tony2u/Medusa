
LayerPushFlags =
{
	None=0,
	ShowPrevScene = 1,
	SuppressUpdateLogic = 2,
	AlwaysCreate = 4,
	DisableTouch = 8,
	HideAllPrevLayers = 16,
	SaveStatusBeforePush = 32,
};

LayerPopFlags =
{
	None=0,
	ShowCurrentLayer = 1,
	SuppressUpdateLogic = 2,
	DisableTouch = 4,
	IgnorePrevLayer = 8,
	DeleteCurrentLayer = 16,
	DeleteCurrentLayerAsync = 32,
	RestoreStatusAfterPop = 64,
};

LayerCreateFlags =
{
	None=0,
	AlwaysCreate = 1,
};

LayerDeleteFlags =
{
	None=0,
	Async = 1,
};

ScenePushFlags =
{
	None=0,
	ShowPrevScene = 1,
	SuppressUpdateLogic = 2,
	DisableTouch = 4,
	HideAllPrevScenes = 8,
};



ScenePopFlags =
{
	None=0,
	ShowCurrentScene = 1,
	SuppressUpdateLogic = 2,
	DisableTouch = 4,
	IgnorePrevScene = 8,
	DeleteCurrentScene = 16,
	DeleteCurrentSceneAsync = 32,
};


