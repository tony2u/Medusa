class SingleStrokeTemplate[Embeded,SuppressCompare,SuppressCopy, Dir=Node/Input/Gesture/Stroke]
{
    string Name;
	PointPath2F Path;
	float BeginAngle;	//for test
	Scale2F BeginScale;
};


class SingleStrokeLibrary[Embeded,SirenConfig,Dir=Node/Input/Gesture/Stroke]
{
	List<SingleStrokeTemplate> Templates[ForceValueToPtr];
};