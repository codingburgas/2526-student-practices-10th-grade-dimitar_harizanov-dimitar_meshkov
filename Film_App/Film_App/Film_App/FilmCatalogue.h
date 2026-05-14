#pragma once
#include "Film.h"
#include <vector>
using namespace std;
namespace FilmCatalogue {
    inline vector<Film> GetAll()
    {
        return {
            {
                "Interstellar",
                "A team of explorers travel through a wormhole to ensure humanity's survival.",
                "Sci-Fi", "Christopher Nolan", "2h 49m",
                8.6f, { 20, 60, 110, 255 }
            },
            {
                "The Dark Knight",
                "Batman faces the Joker, who unleashes chaos on Gotham City.",
                "Action", "Christopher Nolan", "2h 32m",
                9.0f, { 15, 15, 28, 255 }
            },
            {
                "Inception",
                "A thief plants an idea into a target's subconscious through dream-sharing.",
                "Thriller", "Christopher Nolan", "2h 28m",
                8.8f, { 30, 80, 130, 255 }
            },
            {
                "The Matrix",
                "A hacker discovers reality is a simulation and joins a rebellion.",
                "Sci-Fi", "The Wachowskis", "2h 16m",
				8.7f, { 10, 50, 100, 255 }
            },
            {
                "Shutter Island",
                "A U.S. Marshal investigates the disappearance of a murderer from a hospital for the criminally insane.",
                "Mystery / Thriller", "Martin Scorsese", "2h 18m",
                8.2f, { 60, 70, 65, 180}

}
        };
    }
}