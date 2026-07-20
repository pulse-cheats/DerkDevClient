// --- DARKDEV CLIENT CORE LOGIC ---

// 1. FLY MODULE (Movement)
void EnableFly(bool toggle) {
    auto player = Minecraft::getLocalPlayer(); // Παίρνουμε τον παίκτη μας
    if (player && toggle) {
        player->setAbility(MAY_FLY, true);
        player->setAbility(IS_FLYING, true);
        // Αν θέλουμε Jetpack Fly:
        player->motion.y = 0.5f; 
    }
}

// 2. KILLAURA MODULE (Combat)
void RunKillAura() {
    auto player = Minecraft::getLocalPlayer();
    auto entities = Minecraft::getEntities(); // Βρίσκουμε όλους γύρω μας
    
    for (auto entity : entities) {
        if (entity != player && player->distanceTo(entity) < 6.0f) { // Αν είναι κοντά στα 6 blocks
            Minecraft::attack(entity); // Χτύπα αυτόματα!
            player->swing(); // Κάνε το animation του χτυπήματος
        }
    }
}

// 3. X-RAY & ESP (Visuals)
void RunVisuals() {
    // Αλλάζουμε το πώς το παιχνίδι σχεδιάζει τα blocks
    if (darkDevVars.xray) {
        Minecraft::setRenderLayer(STONE, INVISIBLE);
        Minecraft::setRenderLayer(DIRT, INVISIBLE);
    }
    // ESP: Σχεδιάζουμε ένα κουτί γύρω από κάθε παίκτη
    for (auto p : Minecraft::getAllPlayers()) {
        Render::drawBoxAroundEntity(p, Color(255, 0, 0)); // Κόκκινο κουτί
    }
}

// 4. SCAFFOLD (World)
void RunScaffold() {
    auto player = Minecraft::getLocalPlayer();
    Vector3 blockBelow = player->position.subtract(0, 1, 0);
    if (Minecraft::getBlock(blockBelow) == AIR) {
        Minecraft::placeBlock(blockBelow, player->getHeldItem()); // Χτίσε αυτόματα από κάτω
    }
}
