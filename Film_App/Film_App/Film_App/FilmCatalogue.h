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
        };
    }
}