import heapq

class Flight:
    def __init__(self, source, destination, departure, arrival, price):
        self.source = source
        self.destination = destination
        self.departure = parse_time(departure)
        self.arrival = parse_time(arrival)
        self.price = price

# Helper function to convert time strings to minutes since midnight
def parse_time(time_str):
    hour = int(time_str[:2])
    minute = int(time_str[3:5])
    meridian = time_str[5:].strip()

    if meridian == "Am" and hour == 12:
        hour = 0
    elif meridian == "Pm" and hour != 12:
        hour += 12

    return hour * 60 + minute

# Function to find the cheapest flight based on the given constraints
def find_cheapest_flight():
    num_flights = int(input("Enter the number of flights: "))
    flights = []
    flight_map = {}

    # Reading flight details
    for _ in range(num_flights):
        source, destination, departure, arrival, price = input().split()
        price = int(price)
        flight = Flight(source, destination, departure, arrival, price)
        flights.append(flight)

        if source not in flight_map:
            flight_map[source] = []
        flight_map[source].append(flight)

    # Reading start, end cities and time constraints
    start, end = input("Enter start and destination cities: ").split()
    earliest_departure, latest_arrival = input("Enter earliest departure and latest arrival times: ").split()
    earliest_departure = parse_time(earliest_departure)
    latest_arrival = parse_time(latest_arrival)

    # Priority queue for managing flights
    queue = []
    for flight in flight_map.get(start, []):
        if flight.departure >= earliest_departure and flight.arrival <= latest_arrival:
            heapq.heappush(queue, (flight.price, flight.arrival, flight.destination))

    # Tracking minimum costs and arrival times
    min_cost = {}
    arrival_time = {}

    # Processing flights
    while queue:
        cost, current_arrival, city = heapq.heappop(queue)

        # Skip if a better cost or earlier arrival exists
        if city in min_cost and (cost > min_cost[city] or (cost == min_cost[city] and current_arrival >= arrival_time[city])):
            continue

        min_cost[city] = cost
        arrival_time[city] = current_arrival

        if city == end:
            print(f"Cheapest cost to {end}: {cost}")
            return

        # Add connecting flights to the queue
        for flight in flight_map.get(city, []):
            if flight.departure >= current_arrival and flight.departure >= earliest_departure and flight.arrival <= latest_arrival:
                heapq.heappush(queue, (cost + flight.price, flight.arrival, flight.destination))

    print("Flight connection is impossible.")

# Entry point for the script
if __name__ == "__main__":
    find_cheapest_flight()
