local entity = {}
local api = {}


function init(ent, Api) 
	entity.ent = ent
	api.scene = Api:getSceneApi()

	api.scene = Api:getSceneApi()
	api.registry = api.scene:getRegistry()

	api.registry:requestModel(ent, "dev", "lamp")

	entity.transform = api.registry:getTransform(ent)
	scale = entity.transform:getScale()
	scale:setXYZ(0.1, 0.1, 0.1)

	entity.point_light = api.registry:addPointLight(ent)
	entity.point_light:setColor(255, 255, 230);
end

function frame()

end

function update() 
end

function use()
end