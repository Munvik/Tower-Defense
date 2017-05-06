#include "pch.hpp"
#include "buffTower.hpp"
#include "mainGame.hpp"
#include <iomanip>

buffTower::buffTower()
{
	buffArea.setFillColor(sf::Color(120, 220, 0, 55));
}

buffTower::~buffTower()
{
}


void buffTower::activateHUD()
{
	HUDactive = true;
}

void buffTower::unactiveHUD()
{
	HUDactive = false;
}

void buffTower::upgrade()
{
	debuffOtherTowers();

	range = round(range * 1.1f);
	powerBuff = round(powerBuff * 1.3f * 100.f) / 100;
	rangeBuff = round(rangeBuff * 1.3f * 100.f) / 100;
	buffArea.setRadius(range);
	buffArea.setPosition(getMidlePosition(getCenter(), buffArea.getGlobalBounds()));
	value += getUpgradeCost();
	expand();
	upgradeLevel++;

	buffOtherTowers();
}


auto buffTower::getWorkshopTemplate() -> tower::workshopHandler *
{
	if (!workshopTemplate)
	{
		workshopTemplate = std::make_unique<workshopHandler>(this);
	}
	return workshopTemplate.get();
}

tower::shopTemplate * buffTower::getShopTemplate()
{
	if (!storeTemplate)
	{
		storeTemplate = std::make_unique<shopTemplate>(this);
	}

	return storeTemplate.get();
}

bool buffTower::mouseOnHUD(const sf::Vector2f mousePos)
{
	if ((sprite.getGlobalBounds().contains(mousePos) || (isPointOnCircle(mousePos))))
		return true;

	return false;
}

bool buffTower::isPointOnCircle(sf::Vector2f point)
{
	float distance;

	distance = sqrt((getCenter().x - point.x) * (getCenter().x - point.x) + (getCenter().y - point.y) * (getCenter().y - point.y));

	if (distance < range)
		return true;

	return false;
}

void buffTower::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
	
	if (HUDactive)
		target.draw(buffArea);
}

void buffTower::addBuff(buff buffer)
{
	// nothing to do
}

void buffTower::setPosition(sf::Vector2f position)
{
	sprite.setPosition( position);
	buffArea.setPosition(getMiddlePosition(sprite.getGlobalBounds(), buffArea.getGlobalBounds()));
}

bool buffTower::canBuff(tower * tw)
{
	sf::Vector2f towerPoints[4];

	towerPoints[0].x = tw->getPosition().x + tw->getSize().x / 4;
	towerPoints[0].y = tw->getPosition().y + tw->getSize().y / 4;
	towerPoints[1].x = tw->getPosition().x + tw->getSize().x * 3/ 4;
	towerPoints[1].y = tw->getPosition().y + tw->getSize().y / 4;
	towerPoints[2].x = tw->getPosition().x + tw->getSize().x / 4;
	towerPoints[2].y = tw->getPosition().y + tw->getSize().y * 3/4;
	towerPoints[3].x = tw->getPosition().x + tw->getSize().x * 3 / 4;
	towerPoints[3].y = tw->getPosition().y + tw->getSize().y * 3/ 4;

	double distance;

	for (int i = 0; i < 4; ++i)
	{
		distance = sqrt((getCenter().x - towerPoints[i].x)*(getCenter().x - towerPoints[i].x) + 
			(getCenter().y - towerPoints[i].y) * (getCenter().y - towerPoints[i].y));

		if (distance <= range)
			return true;
	}

	return false;
}



//////////////////////////////////////////// BUFFTOWER::WORKSHOPHANDLER ///////////////////////////////
//////////////////////////////////////////// BUFFTOWER::WORKSHOPHANDLER ///////////////////////////////
//////////////////////////////////////////// BUFFTOWER::WORKSHOPHANDLER ///////////////////////////////


void buffTower::workshopHandler::join(workshop *ws)
{
	workshopOwner = ws;
	set();

	if (!Placed())
	{
		place();
	}

	configureUpgrader();
}

void buffTower::workshopHandler::configureUpgrader()
{
	if (owner->isExtended())
		return;

	if ((!goldUpgradeAccesed()) && (owner->isAffordForUpgrade()))
	{
		upgrader.makeAccesibleBackr();
		upgradeAccesed = true;
	}
	else if ((goldUpgradeAccesed()) && (!owner->isAffordForUpgrade()))
	{
		upgrader.makeUnaccesibleBackgr();
		upgradeAccesed = false;
	}
}

bool buffTower::workshopHandler::goldUpgradeAccesed()
{
	return upgradeAccesed;
}

void buffTower::workshopHandler::place()
{
	sf::Vector2f wsSize = workshopOwner->getSize();
	sf::Vector2f wsPos = workshopOwner->getPosition();

	sf::Vector2f upgraderPos;
	upgraderPos.x = wsPos.x + wsSize.x * 3 / 4 - upgrader.getSize().x / 2;
	upgraderPos.y = wsPos.y + wsSize.y / 2 - upgrader.getSize().y / 4;
	upgrader.setPosition(upgraderPos);

	powerBuffFactor.setFont(*font);
	powerBuffFactor.setCharacterSize(20);
	powerBuffFactor.setColor(sf::Color::Red);
	sf::Vector2f powerBuffFactorPos(wsPos.x + wsSize.x / 10, wsPos.y + wsSize.y * 3 / 7 - powerBuffFactor.getGlobalBounds().height / 2);
	powerBuffFactor.setPosition(powerBuffFactorPos);

	rangeBuffFactor.setFont(*font);
	rangeBuffFactor.setCharacterSize(20);
	rangeBuffFactor.setColor(sf::Color::Red);
	sf::Vector2f rangeBuffFactorPos(wsPos.x + wsSize.x * 3 / 10 , wsPos.y + wsSize.y * 3 / 7 - rangeBuffFactor.getGlobalBounds().height / 2);
	rangeBuffFactor.setPosition(rangeBuffFactorPos);

	range.setFont(*font);
	range.setCharacterSize(20);
	range.setColor(sf::Color::Red);
	sf::Vector2f rangePos(wsPos.x + wsSize.x /2 , wsPos.y + wsSize.y * 3 / 7 - range.getGlobalBounds().height / 2);
	range.setPosition(rangePos);

	sf::Vector2f XPos;
	XPos.x = wsPos.x + wsSize.x - X.getGlobalBounds().width;
	XPos.y = wsPos.y;
	X.setPosition(XPos);

	sellText.setFont(*font);
	sellText.setCharacterSize(18);
	sellText.setColor(sf::Color::Red);
	sellText.setString("SELL");
	sf::Vector2f sellTPos;
	sellTPos.x = wsPos.x + wsSize.x - sellText.getGlobalBounds().width;
	sellTPos.y = wsPos.y + wsSize.y - sellText.getGlobalBounds().height * 1.5f;
	sellText.setPosition(sellTPos);

	upgradeCost.setFont(*font);
	upgradeCost.setCharacterSize(20);
	upgradeCost.setColor(sf::Color::Red);
	sf::Vector2f costPos;
	costPos.x = upgrader.getPosition().x + upgrader.getSize().x / 2 - upgradeCost.getGlobalBounds().width / 2;
	costPos.y = upgrader.getPosition().y - upgradeCost.getGlobalBounds().height*1.4f;
	upgradeCost.setPosition(costPos);

	placed = true;
}

void buffTower::workshopHandler::update()
{
	tower::workshopHandler::update();

	if (!owner->isExtended())
	{
		configureUpgrader();
		handleUpgrader();
	}

	handleSeller();
}

void buffTower::workshopHandler::handleSeller()
{
	if (objectClicked(sellText.getGlobalBounds()))
	{
		workshopOwner->leave();
		owner->sell();
	}
}

void buffTower::workshopHandler::handleUpgrader()
{
	if ((upgrader.clicked()) && (upgradeAccesed))
	{
		mainGame::getInstance()->getWallet()->pay(owner->getUpgradeCost());
		owner->upgrade();
		upgrader.upgradeLevel();
		set();
	}
}

void buffTower::workshopHandler::set()
{
	powerBuffFactor.setString("powerFactor = " + floatToString(owner->powerBuff * 100.f)+ "%");
	rangeBuffFactor.setString("rangeFactor = " + floatToString(owner->rangeBuff * 100.f) + "%");

	std::string rangeText;
	float Trange = owner->range;
	if (Trange == 0.f)
	rangeText = "range = nan";
	else
	rangeText = "range = " + floatToString(Trange);

	range.setString(rangeText);

	if (owner->isExtended())
	{
		upgradeCost.setString("MAX");
	}
	else
		upgradeCost.setString("upgrade cost = " + intToString(owner->getUpgradeCost()));

	sf::Vector2f costPos;
	costPos.x = upgrader.getPosition().x + upgrader.getSize().x / 2 - upgradeCost.getGlobalBounds().width / 2;
	costPos.y = upgrader.getPosition().y - upgradeCost.getGlobalBounds().height * 1.4f;
	upgradeCost.setPosition(costPos);
}

void buffTower::workshopHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(X);
	target.draw(powerBuffFactor);
	target.draw(rangeBuffFactor);
	target.draw(range);
	target.draw(upgrader);
	target.draw(sellText);
	target.draw(upgradeCost);
}

////////////////////////// buffTower::shopTemplate ///////////////////////////////////
////////////////////////// buffTower::shopTemplate ///////////////////////////////////
////////////////////////// buffTower::shopTemplate ///////////////////////////////////

buffTower::shopTemplate::shopTemplate(buffTower * ownr)
	:tower::shopTemplate(ownr)
{
	owner = ownr;

	towerSprite = owner->sprite;

	cost.setString("cost=" + intToString(owner->cost));
	cost.setCharacterSize(charSize);
	cost.setColor(sf::Color(240, 24, 24));

	powerBuff.setFont(*font);
	powerBuff.setCharacterSize(charSize);
	powerBuff.setString("powerBuff=" + floatToString(owner->powerBuff*100) + "%");
	powerBuff.setColor(sf::Color(240, 24, 24));

	rangeBuff.setFont(*font);
	rangeBuff.setCharacterSize(charSize);
	rangeBuff.setString("rangeBuff=" + floatToString(owner->rangeBuff*100) + "%");
	rangeBuff.setColor(sf::Color(240, 24, 24));
}

void buffTower::shopTemplate::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	tower::shopTemplate::draw(target, states);
	target.draw(powerBuff);
	target.draw(rangeBuff);
}

void buffTower::shopTemplate::setPosition(sf::Vector2f position)
{
	towerSprite.setPosition(position);

	sf::Vector2f padlockPos = getMiddlePosition(towerSprite.getGlobalBounds(), padlock.getGlobalBounds());
	padlock.setPosition(padlockPos);

	sf::Vector2f costPos;
	costPos.x = towerSprite.getPosition().x + towerSprite.getGlobalBounds().width / 2 - cost.getGlobalBounds().width / 2;
	costPos.y = position.y + towerSprite.getGlobalBounds().height;
	cost.setPosition(costPos);

	sf::Vector2f powerBuffPos;
	powerBuffPos.x = towerSprite.getPosition().x + towerSprite.getGlobalBounds().width / 2 - powerBuff.getGlobalBounds().width / 2;
	powerBuffPos.y = cost.getGlobalBounds().top + cost.getGlobalBounds().height;
	powerBuff.setPosition(powerBuffPos);

	sf::Vector2f rangeBuffPos;
	rangeBuffPos.x = towerSprite.getPosition().x + towerSprite.getGlobalBounds().width / 2 - rangeBuff.getGlobalBounds().width / 2;
	rangeBuffPos.y = powerBuff.getGlobalBounds().top + powerBuff.getGlobalBounds().height;
	rangeBuff.setPosition(rangeBuffPos);
}

sf::Vector2f buffTower::shopTemplate::getSize()
{
	sf::Vector2f size;
	size.x = towerSprite.getGlobalBounds().width / 2;
	size.y = (rangeBuff.getGlobalBounds().top + rangeBuff.getGlobalBounds().height) - towerSprite.getGlobalBounds().top;
	//OR
	//size.y = towerSprite->getGlobalBounds().height + cost.getGlobalBounds().height + powerBuff.getGlobalBounds().height +
		//rangeBuff.getGlobalBounds().height;

	return size;
}
