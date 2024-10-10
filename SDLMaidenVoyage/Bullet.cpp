#include "Bullet.h"


Bullet::Bullet(double PosX, double PosY, Shooter shooter, double TargetX, double TargetY){
	this->PosX = PosX;
	this->PosY = PosY;
	this->DirX = TargetX;
	this->DirY = TargetY;
	this->shooter = shooter;
	bulletDirection = direction(vec2(PosX, PosY), vec2(TargetX, TargetY));
	
	if (shooter == SNIPER) {
		bulletTexture = &sniperBulletTexture;
	}
	else if (shooter == PLAYER) {
		bulletTexture = &playerBulletTexture;
	}
	else {
		bulletTexture = NULL;
	}
	
	
	mCollider.x = PosX;
	mCollider.y = PosY;
	mCollider.w = 25;
	mCollider.h = 25;
	isDestroyed = false;
	std::cout << "Bullet created!\n";
	std::cout << "Shooter: " << shooter << std::endl;
	
}

Bullet::~Bullet() {
	std::cout << "Bullet Destroyed!\n";
}

void Bullet::Update(UpdateContext& context, double timestep) {
	Move();
	if (OutOfBounds()) {
		isDestroyed = true;
	}
	if (HitsWall(context.tiles)) {
		isDestroyed = true;
	}

}

void Bullet::Render(UpdateContext& context) {
	SDL_Rect bulletClip;
	if (shooter == SNIPER) {
		bulletClip = { 620, 350, 90, 80 };
	}
	else if (shooter == PLAYER) {
		bulletClip = { 530, 388, 60, 25 };
	}
	if (bulletTexture != &playerBulletTexture) {
		std::cout << "WTF?????\n" << std::flush;
		bulletTexture = &playerBulletTexture;
	}
	if (IsDead()) {
		std::cout << "we are dead... why are we rendereing\n";
	}
	if (bulletTexture && bulletTexture->GetWidth() > 0 && bulletTexture->GetHeight() > 0) {
		bulletTexture->Render(PosX - context.camera->GetCameraCoords().x, PosY - context.camera->GetCameraCoords().y);
	}
	else {
		std::cerr << "Invalid texture state: Width: "
			<< bulletTexture->GetWidth() << " Height: "
			<< bulletTexture->GetHeight() << std::endl;
	}
}

bool Bullet::IsDead() {
	return isDestroyed;
}

void Bullet::Move() {
	PosX += GetDirection().x * Bullet::PLAYER_FIRE_VELOCITY;
	PosY += GetDirection().y * Bullet::PLAYER_FIRE_VELOCITY;
	mCollider.x = PosX;
	mCollider.y = PosY;
}

vec2 Bullet::GetDirection() {
	return bulletDirection;
}

SDL_Rect Bullet::GetCollider() {
	return mCollider;
}

void Bullet::OnCollide(Entity& entity) {
	if (Player* player = dynamic_cast<Player*>(&entity)) {
		OnCollide(*player);
	}
	else if (Sniper* sniper = dynamic_cast<Sniper*>(&entity)) {
		OnCollide(*sniper);
	}
	else if (Zombie* zombie = dynamic_cast<Zombie*>(&entity)) {
		OnCollide(*zombie);
	}
}

void Bullet::OnCollide(Player& player) {
	if (shooter == SNIPER) {
		isDestroyed = true;
	}
}

void Bullet::OnCollide(Zombie& zombie) {
	if (shooter == PLAYER) {
		isDestroyed = true;
	}
}

void Bullet::OnCollide(Sniper& sniper) {
	if (shooter == PLAYER) {
		isDestroyed = true;
	}
}

bool Bullet::OutOfBounds() {
	SDL_Rect level = { 0, 0, LEVEL_WIDTH, LEVEL_HEIGHT };
	if (!HelperFunctions::EntityInFrame(level, Coordinate(PosX, PosY))) {
		return true;
	}
	return false;
}

bool Bullet::HitsWall(const std::vector<Tile*>& tiles) {

	Coordinate bulletCoordsOnGrid = HelperFunctions::GetNodePointFromWorld(Coordinate(PosX, PosY));
	//FIXFIXFIXFIXFIXFIXFIXFIXFIXFIsssssX
	std::cout << "bullet coordinates converted to grid coordinates: " << bulletCoordsOnGrid << std::endl;
	std::cout << "converted for tile vector: " << bulletCoordsOnGrid.y * TileData::TOTAL_TILES_ROW + bulletCoordsOnGrid.x << std::endl;

	if (tiles[bulletCoordsOnGrid.y * TileData::TOTAL_TILES_ROW + bulletCoordsOnGrid.x]->getType() == 3) {
		return true;
	}
	return false;
}
