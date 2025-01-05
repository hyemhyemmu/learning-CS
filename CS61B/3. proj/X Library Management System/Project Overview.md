Project Background:

A library management system that handles functions such as storing, borrowing, returning, and searching books. The system needs to efficiently manage a large number of books and support multiple search methods.

Main Features:

1. Book Information Storage and Management (using BST)
2. User Information Management (using Hash Tables)
3. Borrowing Record Tracking (using Doubly Linked List)
4. Popular Book Ranking (using Heap)
5. Category Management (using Red-Black Tree)

A. Book Search Function:

- Search by ISBN (Exact match)
- Search by Book Title (Partial match supported, e.g., "Harry" can match "Harry Potter")
- Search by Author (Partial match supported)
- Search by Category (Exact match)
- Support for combined queries (e.g., searching by both Author and Category)

B. Borrowing Function:

- Users can borrow up to 5 books at a time
- Borrowing period is 30 days
- Borrowing history needs to be recorded
- Support for renewal (up to one renewal)

C. Statistical Function:

- Track the most popular books (based on borrowing frequency)
- Query users' borrowing history
- Track currently borrowed books
- Count books by category

项目背景:
一个图书馆管理系统，能处理图书的字储、借阅、归还、搜索等功能。系统需要能够高效地管理大量图书，并支持多种搜索方式

主要功能:
1.图书信息存储和管理(使用BST实现)
2.用户信息管理(使用哈希表实现)
3.借阅记录追踪(使用双向链表实现)
4.热门书籍排行(使用堆实现)
5.分类管理(使用红黑树实现)

A. 图书查找功能:
通过ISBN(精确匹配)
通过书名(支持部分匹配，,，如"Harry"能匹配"Harry Potter")
通过作者(支持部分匹配)
通过分类(精确匹配)
支持组合查询(如同时按作者和分类查询)

B.借阅功能
用户最多同时借阅5本书
借阅期限为30天
需要记录借阅历史
支持续借(最多续借一次)

C.统计功能:
追踪最受欢迎的书籍(基于借阅次数)
用户借阅历史查询
当前借出书籍统计
各分类书籍数量统计
