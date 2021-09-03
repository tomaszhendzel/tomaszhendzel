#pragma once

#include <list>
#include <memory>
#include <functional>
#include <stdexcept>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"

class Event;
class IPort;

namespace Snake
{
struct ConfigurationError : std::logic_error
{
    ConfigurationError();
};

struct UnexpectedEventException : std::runtime_error
{
    UnexpectedEventException();
};

class Segments
{
private:
    struct Segment
    {
        int x;
        int y;
    };
    std::list<Segment> m_segments;
    //Direction m_currentDirection;
    //IPort& m_displayPort;
    //IPort& m_foodPort;
    //IPort& m_scorePort;

    
public:
    /*Segments(/*Direction m_currentDirection/*, IPort& m_displayPort, IPort& m_foodPort, IPort& m_scorePort)
    :/*m_currentDirection(m_currentDirection)/*,m_displayPort(m_displayPort),m_foodPort(m_foodPort), m_scorePort(m_scorePort)
    {
    }*/

    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;

    bool isSegmentAtPosition(int x, int y) const;
    Segment calculateNewHead(Direction m_currentDirection) const;
    void updateSegmentsIfSuccessfullMove(Segment const& newHead, IPort& m_foodPort, IPort& m_scorePort, IPort& m_displayPort);
    void addHeadSegment(Segment const& newHead, IPort& m_displayPort);
    void removeTailSegmentIfNotScored(Segment const& newHead, IPort& m_foodPort, IPort& m_scorePort, IPort& m_displayPort);
    void removeTailSegment(IPort& m_displayPort);
    bool isPositionOutsideMap(int x, int y) const;
    void addSeqment(int x, int y);
    
};

class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    //std::pair<int, int> m_mapDimension;//
    //std::pair<int, int> m_foodPosition;//

    
    Direction m_currentDirection;
    //std::list<Segment> m_segments;
    Segments m_segments ;/*= Segments(m_currentDirection/*, m_displayPort,m_foodPort, m_scorePort/*, m_mapDimension, m_foodPosition);*/
    

    void handleTimeoutInd();
    void handleDirectionInd(std::unique_ptr<Event>);
    void handleFoodInd(std::unique_ptr<Event>);
    void handleFoodResp(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);

//World -ponizsze metody powinny zostac ujete w drugiej klasie
    void updateFoodPosition(int x, int y, std::function<void()> clearPolicy);
    void sendClearOldFood();
    void sendPlaceNewFood(int x, int y);

    bool m_paused;
};

} // namespace Snake
