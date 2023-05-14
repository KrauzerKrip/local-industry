local entity = {}
local api = {}


function init(ent, Api) 
	entity.ent = ent
	api.scene = Api:getSceneApi()

	api.scene:requestModel(ent, "dev", "lamp")

	entity.transform = api.scene:addTransform(ent)
	scale = entity.transform:getScale()
	scale:setXYZ(0.1, 0.1, 0.1)
	entity.transform:setScale(scale)

	entity.point_light = api.scene:addPointLight(ent)
	entity.point_light:setColor(255, 255, 230);
end

function frame()

end

function update() 
	position = entity.transform:getPosition()
	position:setY(position:y() + 0.01)
	--entity.transform:setPosition(position)
	scale = entity.transform:getScale()
	scale:setXYZ(scale:x() + 0.01, scale:y() + 0.01, scale:z() + 0.01)
	--entity.transform:setScale(scale)
end

function use()
end