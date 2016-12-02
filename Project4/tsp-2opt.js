/*************************************************************************************
**************************************************************************************
*****                          ______________                                    *****
*****                    ,===:'.,            `-._                                *****
*****                           `:.`---.__         `-._                          *****
*****                             `:.     `--.         `.                        *****
*****                               \.        `.         `.                      ***** 
*****                       (,,(,    \.         `.   ____,-`.,                   *****
*****                    (,'     `/   \.   ,--.___`.'                            *****
*****                ,  ,'  ,--.  `,   \.;'         `                            *****
*****                 `{D, {    \  :    \;                                       *****
*****                   V,,'    /  /    //                                       *****
*****                   j;;    /  ,' ,-//.    ,---.      ,                       *****
*****                   \;'   /  ,' /  _  \  /  _  \   ,'/                       *****  
*****                         \   `'  / \  `'  / \  `.' /                        *****
*****                          `.___,'   `.__,'   `.__,'  John VanderZwag        *****
**************************************************************************************
* 888888 888888    db    8b    d8     8888b.  88""Yb    db     dP""b8  dP"Yb  88b 88 *
*   88   88__     dPYb   88b  d88      8I  Yb 88__dP   dPYb   dP   `" dP   Yb 88Yb88 *
*   88   88""    dP__Yb  88YbdP88      8I  dY 88"Yb   dP__Yb  Yb  "88 Yb   dP 88 Y88 *
*   88   888888 dP""""Yb 88 YY 88     8888Y"  88  Yb dP""""Yb  YboodP  YbodP  88  Y8 *
**************************************************************************************
** Project 4 - TSP
** Group 34 
** Authors: Mel Drews, Jordan Grant, Adrian Buenavista
** File: tsp-genetic.js
** Description:
                
**************************************************************************************/
var fs = require("fs");

var locationList = [];

locationList.clone = function() {
	var new_array = [];
	
	for (var i = 0; i < this.length; i++) {
		new_array.push(new location(this[i].name, this[i].x, this[i].y));
	}
	
	return new_array;
}

if (process.argv.length < 5) {
    console.log("Arguments Needed: input file, size of population, number of generations");
    process.exit(1);
}
var location = function(name, x, y) {
    this.name = name;
    this.x = x;
    this.y = y;
    this.visited = false;
};

location.prototype.distanceTo = function (locationB) {
    x_dist = Math.abs(this.x - locationB.x);
    y_dist = Math.abs(this.y - locationB.y);

    return Math.round(Math.sqrt(x_dist*x_dist + y_dist* y_dist));
};





//console.log(locationList);

// Individual Tour Object
var ind_tour = function(numberOfLocations) {
    this.dist = 0;
    this.fitness = 0;
    this.route = [];

    for (var i = 0; i < numberOfLocations; i++)
        this.route.push(null);
};

ind_tour.prototype.getFitness = function() {
    if (this.fitness == 0)
        this.fitness = 1 / (this.getDistance());

    return this.fitness;
};

ind_tour.prototype.contains = function(name) {
    for (var i = 0; i < this.route.length; i++){
        if (this.route[i] && this.route[i].name === name) {
            return true;
        }
    }
    return false;
};

ind_tour.prototype.getDistance = function() {
    if (this.dist == 0){
        for (var currCity = 0; currCity < this.route.length; currCity++){
            if (currCity+1 < this.route.length){
                this.dist += this.route[currCity].distanceTo(this.route[currCity+1]);
            } else {
                this.dist += this.route[currCity].distanceTo(this.route[0]);
            }
        }
        return this.dist;
    }
    return this.dist;
};

ind_tour.prototype.clone_region_forward = function(new_tour, start, end) {
	for (var i = start; i <= end; i++) {
		new_tour.route[i] = new location(this.route[i].name, this.route[i].x, this.route[i].y);
	}
}

ind_tour.prototype.clone_region_reverse = function(new_tour, start, end) {
	var j = start;
	for (var i = end; i >= start; i--) {
		new_tour.route[j] = new location(this.route[i].name, this.route[i].x, this.route[i].y);
		j++;
	}
}

//Shuffle function using  Fisher-Yates (aka Knuth) Shuffle from
// http://stackoverflow.com/questions/2450954/how-to-randomize-shuffle-a-javascript-array
ind_tour.prototype.shuffle = function() {
    var currentIndex = this.route.length, temporaryValue, randomIndex;

    // While there remain elements to shuffle...
    while (0 !== currentIndex) {

        // Pick a remaining element...
        randomIndex = Math.floor(Math.random() * currentIndex);
        currentIndex -= 1;

        // And swap it with the current element.
        temporaryValue = this.route[currentIndex];
        this.route[currentIndex] = this.route[randomIndex];
        this.route[randomIndex] = temporaryValue;
    }
};

ind_tour.prototype.random_individual = function() {
    this.route = locationList.slice();
    this.shuffle();
};




// Population Object
var population = function(pop_size, init) {
    this.tourList = [];

    for (var i = 0; i < pop_size; i++) {
        if (init == 1) {
            var temp_tour = new ind_tour(0);
            temp_tour.random_individual();
            this.tourList.push(temp_tour);
        } else if (init == 2) {
			this.tourList.push(nearest_neighbor());
			process.stdout.write("\rSeeded Individual " + (i+1) + " of " + pop_size);
		}else {
            this.tourList.push(null);
        }
    }
	if (init == 2)
		console.log();
};

population.prototype.getFittest = function() {
    var fittest = this.tourList[0];
    for (var i = 1; i < this.tourList.length; i++) {
        if (fittest.getFitness() <= this.tourList[i].getFitness()){
            fittest = this.tourList[i];
        }
    }

    return fittest;
};


function two_opt(start_tour){
	
	var count = 0;
    do {
		var best_distance = start_tour.getDistance();
		var break_out = false;
		for (var i = 0; i < start_tour.route.length - 1; i++) {
			for (var k = i + 1; k < start_tour.route.length; k++) {
				var new_tour = two_opt_swap(start_tour, i, k);
                var new_distance = new_tour.getDistance();
				if (new_distance < best_distance) {
                   start_tour = new_tour;
                   break_out = true;
               } 
			}
			if (break_out == true)
				break;
		}
    process.stdout.write("\rCompleted 2-Opt Round " + (count+1) + " of " + process.argv[4]);
		count++;
	} while (count < process.argv[4]);
  console.log();
	
	return start_tour;
}

function two_opt_swap(tour, i, k) {
    var new_tour = new ind_tour(tour.route.length);
	tour.clone_region_forward(new_tour, 0, i-1);
	tour.clone_region_reverse(new_tour, i, k);
	tour.clone_region_forward(new_tour, k+1, tour.route.length-1);
	return new_tour;
}


// NEAREST NEIGHBOR

function nearest_neighbor() {
    var nnList = locationList.clone();
    var tour = new ind_tour(nnList.length);
	
    var current = Math.round(Math.random() * nnList.length) % nnList.length;
    nnList[current].visited = true;
	var next_index = 0;
    tour.route[next_index] = nnList[current];
	next_index++;
	
    var dist_to_nn = Number.MAX_VALUE;
    var nn_index = -1;

    for (var j = 0; j < nnList.length; j++) {
        for (var k = 0; k < nnList.length; k++){
            if (nnList[k].visited == false) {
                var temp_dist = nnList[current].distanceTo(nnList[k]);
                if (temp_dist < dist_to_nn) {
                    dist_to_nn = temp_dist;
                    nn_index = k;
                }
            }
        }
        if (nn_index != -1) {
            nnList[nn_index].visited = true;
            tour.route[next_index] = nnList[nn_index];
			current = nn_index;
			nn_index = -1;
			next_index++;
			dist_to_nn = Number.MAX_VALUE;
        }
    }
	return tour;
}

// MAIN FUNCTION

function main() {
    var data = fs.readFileSync(process.argv[2]).toString();
    data = data.split('\n');


    for (var i = 0; i < data.length - 1; i++) {
        var location_att = data[i].trim().split(/\s+/);

        var name = location_att[0];
        var x = location_att[1];
        var y = location_att[2];

        var temp_location = new location(name, x, y);

        locationList.push(temp_location);
    }


// create population to start
    var pop = new population(process.argv[3], 2);

    console.log("initial distance: " + pop.getFittest().getDistance());

    var best = pop.getFittest();
    best = two_opt(best);
    console.log("Final Distance: " + best.getDistance());
	
	var buffer = best.getDistance().toString();
	

    for (var i = 0; i < best.route.length; i++) {
        console.log(best.route[i].name);
		buffer += "\n" + best.route[i].name;
	}
	buffer += "\n";
	//buffer = Buffer.from(buffer, 'utf8');

	fs.open(process.argv[2] + ".tour", 'w', function(err, fd) {
		if (err) {
			throw 'error opening file: ' + err;
		}

		fs.write(fd, buffer, 0, buffer.length, null, function(err) {
			if (err) throw 'error writing file: ' + err;
			fs.close(fd, function() {
				console.log('file written');
			})
		});
	});
}


main();

