local entity = {}
local api = {}


function init(ent, Api) 
	entity.ent = ent
	api.scene = Api:getSceneApi()

	api.scene:addModel(ent, "dev", "lamp")

	entity.transform = api.scene:addTransform(ent)
end

function frame()
  
end

function update() 

end

function use()
end