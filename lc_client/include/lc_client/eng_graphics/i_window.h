class IWindow {
public: 
	virtual ~IWindow() {}
	
	virtual void init() = 0;
	virtual void update() = 0;
};