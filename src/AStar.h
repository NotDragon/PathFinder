#pragma once

#include <vector>
#include <algorithm>
#include "PathAlgorithm.h"
#include "Node.h"

class AStarNode : public Node
{
	public:

		AStarNode()
		{
			m_f = m_g = m_h = 0.0;
			closed = open = false;
		}

		virtual ~AStarNode()
		{}

		void setPosition(int x, int y)
		{
			m_x = x;
			m_y = y;
		}

		void setF(float f)
		{
			m_f = f;
		}

		void setG(float g)
		{
			m_g = g;
		}

		void setH(float h)
		{
			m_h = h;
		}

		void setOpen(bool value)
		{
			open = value;
		}

		void setClosed(bool value)
		{
			closed = value;
		}

		inline unsigned int getX() const
		{
			return m_x;
		}

		inline unsigned int getY() const
		{
			return m_y;
		}

		inline float getF() const
		{
			return m_f;
		}

		inline float getG() const
		{
			return m_g;
		}

		inline float getH() const
		{
			return m_h;
		}

		inline bool isOpen() const
		{
			return open;
		}

		inline bool isClosed() const
		{
			return closed;
		}

		std::vector<std::pair<AStarNode*, float>>& getChildren()
		{
			return reinterpret_cast<std::vector<std::pair<AStarNode*, float>>&>(m_children);
		}

		float distanceTo(AStarNode* node) const
		{
			int newX = m_x - node->getX(), newY = m_y - node->getY();
			return static_cast<float>(sqrt(newX*newX + newY*newY));
		}

		void release()
		{
			open = closed = false;
			m_f = m_g = m_h = 0.0f;
			m_parent = nullptr;
		}

	protected:
		float m_f, m_g, m_h;
		unsigned int m_x, m_y;
		bool open, closed;
};

struct CompareNodes
{
	bool operator() (const AStarNode* s1, const AStarNode *s2) const
	{
		return s1->getF() < s2->getF();
	}
};

class AStar : public PathAlgorithm<AStarNode>
{
	public:
		AStar();
		~AStar();
		
		bool getPath(std::vector<AStarNode*>& path);
		void clear();

	private:
		void releaseNodes();
		void pushOpen(AStarNode* node);
		void popOpen(AStarNode* node);
		
		std::vector<AStarNode*> open, closed;
};
