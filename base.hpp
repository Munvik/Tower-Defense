#pragma once
#include "tower.hpp"
#include "buffTower.hpp"
class base :public tower
{
	void loadTexture();
	void setAttributes();
public:
	base();
	~base();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void update();
	void upgrade();

	void unactiveHUD() override;
	void activateHUD() override;

	tower::workshopHandler *getWorkshopTemplate() override;
	tower::shopTemplate *getShopTemplate() override;
	std::shared_ptr<tower> getClassObject();
	bool mouseOnHUD(const sf::Vector2f mousePos);
	void addBuff(buff buffer) override;

	class workshopHandler;
};

class base::workshopHandler : public tower::workshopHandler
{
	base *owner;
public:
	workshopHandler(base *ownr);
	void join(class workshop *ws) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void update() override;
	void set() override;
};