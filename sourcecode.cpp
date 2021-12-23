#include <iostream>
#include <stdlib.h>
using namespace std;

// A structure for building
struct Building {

    int x_coordinate;
    int y_coordinate;
    int height;

};

// A class that is used to represent a strip
class Strip {

    int x_coordinate;
    int height;

    //The constructor that assigns value to the strip created
    public:
        Strip(int building_length = 0, int building_height = 0)
        {
            x_coordinate = building_length;
            height = building_height;
        }

        friend class SkyLine;
};


int maximum(int a, int b)
{
    //Calculates maximum of two numbers
    return( max(a,b));
}

// This class stores the resulted skyline in an array of strips
class SkyLine {

    Strip* skystrip;             //This array of strips represent the resulting skyline
    int size_of_array;          // The actual size of the array that is filled.
    int capacity;               //The maximum number of strips the array can hold


public:
    ~SkyLine() { delete[] skystrip; }

    int count(){ return size_of_array; }

    void print();               // A function that prints the skyline

    SkyLine* MergeSkyline(SkyLine* second);

    // Constructor
    SkyLine(int total_num)
    {
        capacity = total_num;
        skystrip = new Strip[capacity];
        size_of_array = 0;
    }

    // Function to add a strip 'st' to array
    void append(Strip* s)
    {
        // Check for redundant strip, a strip is
        // redundant if it has same height or x_coordinate as previous
        if (size_of_array > 0 && skystrip[size_of_array - 1].height == s->height)
            return;
        if (size_of_array > 0 && skystrip[size_of_array - 1].x_coordinate == s->x_coordinate) {
            skystrip[size_of_array - 1].height = maximum(skystrip[size_of_array - 1].height, s->height);
            return;
        }

        skystrip[size_of_array] = *s;
        size_of_array++;
    }

};

void SkyLine::print()
{
        for (int i = 0; i < size_of_array; i++) {
            cout << " (" << skystrip[i].x_coordinate << ", "
                 << skystrip[i].height << "), "<<"\n";
        }
        cout<<"------- Skyline end here -------"<<"\n\n\n";
}


SkyLine* findSkyline(Building build[], int start, int last)
{
    if (start == last) {
        SkyLine* final_skyline = new SkyLine(2);

        //
        final_skyline->append(new Strip(build[start].x_coordinate, build[start].height));
        final_skyline->append(new Strip(build[start].y_coordinate, 0));
        return final_skyline;
    }

    int building_mid = (start + last) / 2;

    // These lines are to recursively divide the left and right skylines.
    SkyLine* left_skyline = findSkyline(build, start, building_mid);
    SkyLine* right_skyline = findSkyline(build, building_mid + 1, last);

    // After the skylines have been divided, they can be merged on applying the rule
    SkyLine* final_skyline = left_skyline->MergeSkyline(right_skyline);


    delete left_skyline;
    delete right_skyline;
    return final_skyline;
}


// The function that merges the two skylines into one
SkyLine* SkyLine::MergeSkyline(SkyLine* second)
{
    //The resulting skyline has the capacity of storing two skylines i.e. the left skyline and the right skyline
    SkyLine* resulting = new SkyLine(this->size_of_array + second->size_of_array);

    // To store current heights of two skylines
    int height1 = 0, height2 = 0;

    int i = 0, j = 0;           //Variable to loop through the two skylines
    while (i < this->size_of_array && j < second->size_of_array)
        {
        if (this->skystrip[i].x_coordinate < second->skystrip[j].x_coordinate)
        {
            int x1 = this->skystrip[i].x_coordinate;
            height1 = this->skystrip[i].height;
            // Choose height as max of two heights
            int max_height = maximum(height1, height2);
            resulting->append(new Strip(x1, max_height));
            i++;
        }
        else {
            int x2 = second->skystrip[j].x_coordinate;
            height2 = second->skystrip[j].height;
            int maxheight = maximum(height1, height2);
            resulting->append(new Strip(x2, maxheight));
            j++;
        }
    }

    // If there are strips x_coordinate in this
    // skyline or other skyline
    while (i < this->size_of_array) {
        resulting->append(&skystrip[i]);
        i++;
    }
    while (j < second->size_of_array) {
        resulting->append(&second->skystrip[j]);
        j++;
    }
    return resulting;
}


void mergeArray(Building* sort_array, int left, int middle, int right)
{
    int m1 = middle - left + 1;
    int m2 = right - middle;
    Building left_array[m1];
    Building right_array[m2];

    for(int i = 0 ; i<m1 ; i++)
    {
        left_array[i].x_coordinate = sort_array[left+i].x_coordinate;
        left_array[i].y_coordinate = sort_array[left+i].y_coordinate;
        left_array[i].height = sort_array[left+i].height;
    }

     for(int i = 0 ; i<m2 ; i++)
    {
        right_array[i].x_coordinate = sort_array[middle+1+i].x_coordinate;
        right_array[i].y_coordinate = sort_array[middle+1+i].y_coordinate;
        right_array[i].height = sort_array[middle+1+i].height;
    }

    // --------------------------------- >

    int i = 0;
    int j = 0;
    int k = left;
    while(i<m1 && j<m2)
    {
        if(left_array[i].x_coordinate <= right_array[j].x_coordinate)
        {
            sort_array[k].x_coordinate = left_array[i].x_coordinate;
            sort_array[k].y_coordinate = left_array[i].y_coordinate;
            sort_array[k].height = left_array[i].height;
            i++;
        }
        else
        {
            sort_array[k].x_coordinate = right_array[j].x_coordinate;
            sort_array[k].y_coordinate = right_array[j].y_coordinate;
            sort_array[k].height = right_array[j].height;
            j++;
        }
        k++;
    }

    while(i<m1)
    {
        sort_array[k].x_coordinate = left_array[i].x_coordinate;
        sort_array[k].y_coordinate = left_array[i].y_coordinate;
        sort_array[k].height = left_array[i].height;
        i++;
        k++;
    }

    while(j<m2)
    {
        sort_array[k].x_coordinate = right_array[j].x_coordinate;
        sort_array[k].y_coordinate = right_array[j].y_coordinate;
        sort_array[k].height = right_array[j].height;
        j++;
        k++;
    }
}
void mergeGivenArray(Building* sort_array, int s, int m, int e)
{
    int i;
    int sum = 0;
    int mid = m;
    for(i  = 0 ; i<10 ; i++)
    {
        sum = sum + sort_array[i].x_coordinate;
    }
    mergeArray(sort_array, s, m, e);
}

void mergesort(Building* sort_array, int left, int right)
{
    if(left>=right)
    {
        return;
    }
    int middle = (left + right)/2;
    mergesort(sort_array, left, middle);
    mergesort(sort_array, middle+1, right);
    mergeGivenArray(sort_array, left, middle, right);
}

// Driver Function
int main()
{
    // Counter variables-
    int i, j;


    //------------------ 10 BUILDINGS ------------------------>
    //Building array consisting of 1000 building coordinates ----->
    Building building_array_10[10];
    int size_of_array_10 = sizeof(building_array_10) / sizeof(building_array_10[0]);
    for(i=0 ; i<10 ; i++)
    {
        //Creating array by inserting random values ---->
        building_array_10[i].x_coordinate = rand() % 100;
        //Making sure that the value of y_coordinate is always greater than x_coordinate ----->
        building_array_10[i].y_coordinate = building_array_10[i].x_coordinate + rand() % 20 + 1;
        building_array_10[i].height = rand() % 80;

    }
    //SORTING THE ABOVE BUILDING ARRAYS ON THE BASIS OF X-COORDINATES OF THE BUILDINGS
    mergesort(building_array_10, 0, size_of_array_10-1);
    cout<<"Building 10 array AFTER MERGESORT ----> \n";
    for(i=0 ; i<10 ; i++)
    {
        cout<<"( "<< building_array_10[i].x_coordinate <<", "<< building_array_10[i].y_coordinate <<", "<<building_array_10[i].height<<" )\n";
    }
    SkyLine* pointer_10 = findSkyline(building_array_10, 0, size_of_array_10 - 1);
    cout << " Skyline for 10 buildings is \n";
    pointer_10->print();



    //-------------------------- 100 BUILDINGS -------------------------------->
    //Repeating the above steps for array that consists of 100 buildings ---->
    //Building array consisting of 1000 building coordinates
    Building building_array_100[100];
    int size_of_array_100 = sizeof(building_array_100) / sizeof(building_array_100[0]);
    for(i=0 ; i<100 ; i++)
    {
        building_array_100[i].x_coordinate = rand() % 500;
        building_array_100[i].y_coordinate = building_array_100[i].x_coordinate + rand() % 20 + 1;
        building_array_100[i].height = rand() % 80;
    }
    mergesort(building_array_100, 0, size_of_array_100 - 1);
    SkyLine* pointer_100 = findSkyline(building_array_100, 0, size_of_array_100 - 1);
    cout << " Skyline for 100 buildings is \n";
    pointer_100->print();




    //--------------------------- 1000 BUILDINGS --------------------------------->
    //Repeating the above steps for array that consists of 1000 buildings ---->
    //Building array consisting of 1000 building coordinates
    Building building_array_1000[1000];
    int size_of_array_1000 = sizeof(building_array_1000) / sizeof(building_array_1000[0]);
    for(i=0 ; i<1000 ; i++)
    {
        building_array_1000[i].x_coordinate = rand() % 1000;
        building_array_1000[i].y_coordinate = building_array_1000[i].x_coordinate + rand() % 30 + 1;
        building_array_1000[i].height = rand() % 80;
    }
    mergesort(building_array_1000, 0, size_of_array_1000-1);
    SkyLine* pointer_1000 = findSkyline(building_array_1000, 0, size_of_array_1000 - 1);
    cout << " Skyline for 1000 buildings is \n";
    pointer_1000->print();



    //--------------------------- 10,000 BUILDINGS --------------------------------->
    //Repeating the above steps for array that consists of 10,000 buildings ---->
    //Building array consisting of 10,000 building coordinates
    Building building_array_10000[10000];
    int size_of_array_10000 = sizeof(building_array_10000) / sizeof(building_array_10000[0]);
    for(i=0 ; i<10000 ; i++)
    {
        building_array_10000[i].x_coordinate = rand() % 10000;
        building_array_10000[i].y_coordinate = building_array_10000[i].x_coordinate + rand() % 50 + 1;
        building_array_10000[i].height = rand() % 80;
    }
    mergesort(building_array_10000, 0, size_of_array_10000-1);
    SkyLine* pointer_10000 = findSkyline(building_array_10000, 0, size_of_array_10000 - 1);
    cout << " Skyline for 10000 buildings is \n";
    pointer_10000->print();


/*
//--------------------------- 100,000 BUILDINGS --------------------------------->
    //Repeating the above steps for array that consists of 10,000 buildings ---->
    //Building array consisting of 10,000 building coordinates
    Building building_array_100000[100000];
    int size_of_array_100000 = sizeof(building_array_100000) / sizeof(building_array_100000[0]);
    for(i=0 ; i<10000 ; i++)
    {
        building_array_100000[i].x_coordinate = rand() % 100000;
        building_array_100000[i].y_coordinate = building_array_100000[i].x_coordinate + rand() % 50 + 1;
        building_array_100000[i].height = rand() % 80;
    }
    mergesort(building_array_100000, 0, size_of_array_100000-1);
    SkyLine* pointer_100000 = findSkyline(building_array_100000, 0, size_of_array_100000 - 1);
    cout << " Skyline for 10000 buildings is \n";
    pointer_100000->print();
*/

    return 0;
}
