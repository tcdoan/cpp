namespace td
{
  class Point
  {
  public:
    Point();
    Point(int x, int y);
    int GetX();    
    int GetY();
    void SetX(int);
    void SetY(int);        
  private:
    int x;
    int y;
  }
}
