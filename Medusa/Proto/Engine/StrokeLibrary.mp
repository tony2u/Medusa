class SingleStrokeTemplate[Embeded,SuppressCompare,SuppressCopy, Dir=Node/Input/Gesture/Stroke]
{
    string Name;
	PointPath2F Path;
};


class SingleStrokeLibrary[Embeded,SirenConfig,Dir=Node/Input/Gesture/Stroke]
{
	List<SingleStrokeTemplate> Templates[ForceValueToPtr];
};