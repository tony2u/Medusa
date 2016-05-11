module(..., package.seeall);

function NewSprite(textureName,textureRect)
	return ml.NodeFactory.CreateQuadSprite(textureName,textureRect);
end
