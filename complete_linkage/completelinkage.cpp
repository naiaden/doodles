#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <tuple>

/*
 * A simple Point class with two integer coordinates and a label
 */
class Point
{
    std::string label;
    int x, y;
public:
    Point(const std::string& label = "", int x = 0, int y = 0) : label(label), x(x), y(y)
    {    }
    
    std::string getLabel() const 
    {
        return label;
    }
    
    std::tuple<int, int> getPosition() const
    {
        return std::tuple<int, int>(x, y);
    }
    
    double getDistance(const Point& point) const
    {   // pythagoras
        return sqrt(abs(pow(x,2)-pow(std::get<0>(point.getPosition()),2)) + abs(pow(y,2)-pow(std::get<1>(point.getPosition()),2)));
    }
    
    std::string toString() const
    {
        std::ostringstream ss;
        ss << label << "(" << x << "," << y << ")";
        return ss.str();
    }
    
    bool operator==(const Point& p) const
    {
        return label == p.getLabel() && getPosition() == p.getPosition();
    }
    
    bool operator!=(const Point& p) const
    {
        return !(label == p.getLabel() && getPosition() == p.getPosition());
    }
};

class Cluster
{
    std::vector<Point> points;
    std::string label;
    
public:    
    Cluster(const std::string& label, const std::vector<Point>& points) : label(label), points(points)
    {    }
    
    Cluster(const std::string& label, const Point& point) : label(label)
    {
        points.push_back(point);
    }

    Cluster()
    {    }

    std::string toString(bool showElements = false) const
    {
         std::ostringstream ss;
         ss << label << "[" << length();
         if(showElements)
         {
            ss << ":";
            for(Point p: points)
            {
                ss << " " << p.toString();
            }
         }
         ss << "]";
         return ss.str();
    }

    std::vector<Point> getPoints() const
    {
        return points;
    }
    
    std::string getLabel() const
    {
        return label;
    }
    
    std::vector<Point> takePoints()
    {
        std::vector<Point> p = points;
        points.clear();
        return p;
    }

    void merge(Cluster& c)
    {
        std::vector<Point> newPoints = c.takePoints();
        points.insert(std::end(points), std::begin(newPoints), std::end(newPoints));
    }

    std::tuple<double, Point, Cluster, Point> findMaxDistance(const Cluster& c) const
    {
        Point maxP1;
        Point maxP2;
        Cluster maxC2;
    
        double maxDistance = 0.0;
        for(auto p1: points)
        {
            for(auto p2: c.getPoints())
            {
                if(p1.getDistance(p2) > maxDistance)
                {
                    maxDistance = p1.getDistance(p2);
                    
                    maxP1 = p1;
                    maxP2 = p2;
                    maxC2 = c;
                }
            }
        }
//        std::cout << maxDistance << " " << maxP1.toString() << " " << maxP2.toString() << std::endl;
        return std::tuple<double, Point, Cluster, Point>(maxDistance, maxP1, maxC2, maxP2);
    }

    int length() const
    {
        return points.size();
    }
    
    bool operator==(const Cluster& cluster) const
    {
        return label == cluster.getLabel() && length() == cluster.length() && points == cluster.getPoints();
    }
    
    bool operator!=(const Cluster& cluster) const
    {
        return !(label == cluster.getLabel() && length() == cluster.length() && points == cluster.getPoints());
    }
};

int main()
{   // First define the initial clusters, one cluster per point is a default assumption
    Cluster c1("A", Point("P1", 0, 1));
    Cluster c2("B", Point("P2", 3, 5));
    Cluster c3("C", Point("P3", 2, 3));
    Cluster c4("D", Point("P4", 1, 4));
    Cluster c5("E", Point("P5", 2, 4));
    Cluster c6("F", Point("P6", 4, 4));
    
    std::vector<Cluster> clusters {c1, c2, c3, c4, c5, c6};
    
    for(Cluster c: clusters)
    {
        std::cout << c.toString(true) << std::endl;
    }
    
    int samples = 0;
    while(clusters.size() > 1)
    {
        std::cout << "============================================ " << ++samples << std::endl;
        std::vector<std::tuple<Cluster, std::tuple<double, Point, Cluster, Point> > > minTuples;
        for(auto c1: clusters)
        {
            // For each other cluster c2, compute the distance to the nodes in c2 that are 
            // the furthest away from the nodes in c1
            std::vector<std::tuple<double, Point, Cluster, Point> > c1Tuples;
            for(auto c2: clusters)
            {
                if(c1 != c2)
                {
                    c1Tuples.push_back(c1.findMaxDistance(c2));
                }
            }
            
            // Now store the cluster which is at the largest distance for c1
            std::tuple<double, Point, Cluster, Point> c1MaxTuple;
            bool firstIter = true;
            for(std::tuple<double, Point, Cluster, Point> t: c1Tuples)
            {
                if(firstIter)
                {
                    c1MaxTuple = t;
                    firstIter = false;
                }
                
                if(std::get<0>(c1MaxTuple) < std::get<0>(t))
                {
                    c1MaxTuple = t;
                }
            }

            std::cout << "----" << std::get<0>(c1MaxTuple) << "(" << std::get<1>(c1MaxTuple).toString() << "," << std::get<3>(c1MaxTuple).toString() << ")" << std::endl;
            minTuples.push_back(std::tuple<Cluster, std::tuple<double, Point, Cluster, Point> >(c1, c1MaxTuple));
        }
        
        // Since we want the minimum maximum distance, we now search for the closest distances,
        // with the distances we found above
        std::tuple<Cluster, std::tuple<double, Point, Cluster, Point> > minTuple;
        bool firstIter = true;
        
        for(std::tuple<Cluster, std::tuple<double, Point, Cluster, Point> > t : minTuples)
        {
            if(firstIter)
            {
                minTuple = t;
                firstIter = false;
            }
            
            if(std::get<0>(std::get<1>(minTuple)) > std::get<0>(std::get<1>(t)))
            {
                minTuple = t;
            }
        }
        std::cout << "Merging " << std::get<0>(minTuple).toString() << " with " << std::get<2>(std::get<1>(minTuple)).toString() << " because of points " << std::get<1>(std::get<1>(minTuple)).toString() << " and " << std::get<3>(std::get<1>(minTuple)).toString() << " with distance " << std::get<0>(std::get<1>(minTuple)) << std::endl;

        // Merge the clusters (This ugly piece of code is because of some issues with references and objects)
        std::vector<Cluster>::iterator iter = std::find(clusters.begin(), clusters.end(), std::get<0>(minTuple));
        if(iter != clusters.end())
        {
            std::vector<Cluster>::iterator iter2 = std::find(clusters.begin(), clusters.end(), std::get<2>(std::get<1>(minTuple)));
            if(iter2 != clusters.end())
            {
                iter->merge(*iter2);
            }
        }

        // Remove the empty clusters
        clusters.erase(std::remove_if(
            clusters.begin(), clusters.end(),
            [](const Cluster& c) {
                return c.length() == 0;
            }), clusters.end());
        
        for(Cluster c: clusters)
        {
            std::cout << c.toString(true) << std::endl;
        }
    }
}
