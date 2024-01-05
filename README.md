# Boid Simulation #

## About: ##  
My Boid Simulation is a surreal artificial life experience that produces realistic scenarios that resemble the flocking behaviour of not just birds but also fish. There are 3 different themes to choose from ranging from Birds to Fish and even Rabbits (flying rabbits I know). Additionally, Static Obstacles and Dynamic Obstacles can be spawned in, which help demonstrate the boids inherited realistic Obstacle Avoidance mechanism, that utilises Pursuing and Evasion. Alongside this, boids are constrained to a bounding box, in which its size can be changed on all 3 axis (x, y, z). I have introduced a Truncated Running sum with priority into the Application of Flocking behaviours. This allows me to prioritise particular flocking behaviours such as Separation, Cohesion and Alignment as well as Wandering (this aims to mimic random movement amongst the boids making each simulation different from the last). 
Moreover, there is a Free Fly mode in which the Player can openly fly about in the simulation and gain a closer insight into analysing the boids behaviours from different angles, perspectives and distances.

There is a wide variety of UI customisation that the Player can tweak in order to create an abundance of many different scenarios and help make the simulation their own. 

The UI Features that can be customised are noted below:

**<ins>Boid Settings:<ins>**
- Number of Boids to spawn [0 -> 500]
- Spawn Radius [0 -> 15000]
- Neighbour Radius [0 -> 7500]
- Separation Weight [-3 -> 3]
- Cohesion Weight [-3 -> 3]
- Alignment Weight [-3 -> 3]
- Speed [0 -> 10000]
- Max Velocity [0 -> 25]
- Constrain Force [0 -> 5]
- Spawn Boids [Button]
- Free Fly [Button]
- Reset Settings to Defaults [Button]

**<ins>Boid Extra Settings:<ins>** 
- Bounding Box Size X [1000 -> 10000]
- Bounding Box Size Y [1000 -> 10000]
- Bounding Box Size Z [1000 -> 10000]
- Number of Static Obstacles to spawn [0 -> 25]
- Number of Dynamic Obstacles to spawn [0 -> 5]
- Boid Avoidance CheckBox [ON/OFF]
- Obstacle Avoidance CheckBox [ON/OFF]
- Slow-Motion CheckBox [ON/OFF]
- Draw Debug Box CheckBox [ON/OFF]
- Spawn Static Obstacles [Button]
- Spawn Dynamic Obstacles [Button]
- Reset Extra Settings to Defaults [Button]

**<ins>Boid Theme Settings:<ins>**
- Switch to Bird Theme [Button]
- Switch to Fish Theme [Button]
- Switch to Rabbit Theme [Button]

## **Assets used in Project:**

- Nick Veselov #NVJOB (2020), "Simple Boids (Flocks of Birds, Fish and Insects)", [online], Unity Asset Store,    
Available at: https://assetstore.unity.com/packages/3d/characters/animals/simple-boids-flocks-of-birds-fish-and-insects-164188,      (Accessed: December 2023)  

- Alstra Infinite (2021), "Fish - PolyPack", [online], Unity Asset Store,      
Available at: https://assetstore.unity.com/packages/3d/characters/animals/fish/fish-polypack-202232,        
(Accessed: December 2023)

- Niwashi Games (2019), "White Rabbit", [online], Unity Asset Store,    
Available at: https://assetstore.unity.com/packages/3d/characters/animals/white-rabbit-138709,      
(Accessed: December 2023)  

- PROTOFACTOR INC (2018), "ANIMAL VARIETY PACK", [online], Epic Games UE Marketplace,    
Available at: https://www.unrealengine.com/marketplace/en-US/product/17c2d7d545674204a7644c3c0c4c58ba,  
(Accessed: December 2023)

- reeel (2023), "Black side silhouette of a rabbit isolated on white background", [online], Adobe Stock,  
Available at: https://stock.adobe.com/uk/search?k=bunny+silhouette,  
(Accessed: December 2023)

- 左卫门 (2023), "Fish Silhouette Cartoon Cute Silhouette Transparent Background", [online], Png Tree,  
Available at: https://pngtree.com/freepng/fish-silhouette-cartoon-cute_6324661.html,  
(Accessed: December 2023)

- Rebecca Evans (2023), "silhouette_bird_flight", [online], Pinterest,  
Available at: https://www.pinterest.co.uk/pin/silhouette_bird_flight_by_-clipart-best-clipart-best--298222806548591476/,    
(Accessed: December 2023)

## **Websites used in Project:**
- Harrison McGuire (2017), "Unreal Engine 4 C++ Tutorial: Draw Debug Helpers", [online], YouTube,    
Available at: https://www.youtube.com/watch?v=XPzkCafs1rU,  
(Accessed: Novemeber 2023)

- Fernando Bevilacqua (2012), "Understanding Steering Behaviors: Pursuit and Evade", [online], envato tuts+,      
Available at: https://code.tutsplus.com/understanding-steering-behaviors-pursuit-and-evade--gamedev-2946t,    
(Accessed: Novemeber 2023)

## **Sounds used in Project:**
- EminYILDIRIM (2020), "UI Pop Up" [online], freesound.org,  
Available at: https://freesound.org/people/EminYILDIRIM/sounds/540568/,  
(Accessed: December 2023)

- EminYILDIRIM (2020), "Bottle Pop Up UI" [online], freesound.org,  
Available at: https://freesound.org/people/EminYILDIRIM/sounds/539167/,  
(Accessed: December 2023)

- benzix2 (2019), "UI Button Click" [online], freesound.org,  
Available at: https://freesound.org/people/benzix2/sounds/467951/,  
(Accessed: December 2023)

- javapimp (2018), "Pop 5.ogg" [online], freesound.org,  
Available at: https://freesound.org/people/javapimp/sounds/439186/,  
(Accessed: December 2023)

By Josh Brown :D
