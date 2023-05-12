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
	entity.point_light:setColor(255, 255, 255);
end

function frame()

end

function update() 

end

function use()
end