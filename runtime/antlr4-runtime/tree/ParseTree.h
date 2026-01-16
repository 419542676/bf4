/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

#pragma once

#include "support/Any.h"
#include "tree/ParseTreeType.h"

namespace antlr4 {
namespace tree {

  /// An interface to access the tree of <seealso cref="RuleContext"/> objects created
  /// during a parse that makes the data structure look like a simple parse tree.
  /// This node represents both internal nodes, rule invocations,
  /// and leaf nodes, token matches.
  ///
  /// The payload is either a <seealso cref="Token"/> or a <seealso cref="RuleContext"/> object.
  // ml: This class unites 4 Java classes: RuleNode, ParseTree, SyntaxTree and Tree.
  ///ParseTree 类是ANTLR 4中的一个抽象基类，它定义了解析树节点的基本接口。这个类可以代表内部节点（规则调用）、叶子节点（标记匹配）等。解析树的节点可以包含以下信息：
  ///父节点(parent): 指向当前节点的父节点的指针。如果返回的是nullptr，则表示当前节点是树的根节点。
  ///子节点(children): 存储子节点的向量。如果当前节点是叶子节点，则这个向量为空
  class ANTLR4CPP_PUBLIC ParseTree {
  public:
    ParseTree(ParseTree const&) = delete;

    virtual ~ParseTree() = default;

    ParseTree& operator=(ParseTree const&) = delete;

    /// The parent of this node. If the return value is null, then this
    /// node is the root of the tree.
    ParseTree *parent = nullptr;

    /// If we are debugging or building a parse tree for a visitor,
    /// we need to track all of the tokens and rule invocations associated
    /// with this rule's context. This is empty for parsing w/o tree constr.
    /// operation because we don't the need to track the details about
    /// how we parse this rule.
    // ml: memory is not managed here, but by the owning class. This is just for the structure.
    std::vector<ParseTree *> children;

    /// Print out a whole tree, not just a node, in LISP format
    /// {@code (root child1 .. childN)}. Print just a node if this is a leaf.
    ///以LISP格式打印整个树（包括根节点和所有子节点），如果是叶子节点则只打印该节点。
    /// pretty参数用于控制输出格式是否更易读
    virtual std::string toStringTree(bool pretty = false) = 0;
    ///打印当前节点的信息。
    virtual std::string toString() = 0;

    /// Specialize toStringTree so that it can print out more information
    /// based upon the parser.
    ///一个特殊化的 toStringTree 方法，可以基于解析器打印更多信息。
    virtual std::string toStringTree(Parser *parser, bool pretty = false) = 0;
    ///重载等于操作符，用于比较两个ParseTree对象是否相等
    virtual bool operator == (const ParseTree &other) const;

    /// The <seealso cref="ParseTreeVisitor"/> needs a double dispatch method.
    // ml: This has been changed to use Any instead of a template parameter, to avoid the need of a virtual template function.
    ///接受一个访问者对象的访问，这是访问者模式中的一个核心方法。
    /// 它允许访问者对象对解析树进行遍历和操作。
    virtual std::any accept(ParseTreeVisitor *visitor) = 0;

    /// Return the combined text of all leaf nodes. Does not get any
    /// off-channel tokens (if any) so won't return whitespace and
    /// comments if they are sent to parser on hidden channel.
    ///返回所有叶子节点的文本内容的组合。
    virtual std::string getText() = 0;

    /**
     * Return an {@link Interval} indicating the index in the
     * {@link TokenStream} of the first and last token associated with this
     * subtree. If this node is a leaf, then the interval represents a single
     * token and has interval i..i for token index i.
     *
     * <p>An interval of i..i-1 indicates an empty interval at position
     * i in the input stream, where 0 &lt;= i &lt;= the size of the input
     * token stream.  Currently, the code base can only have i=0..n-1 but
     * in concept one could have an empty interval after EOF. </p>
     *
     * <p>If source interval is unknown, this returns {@link Interval#INVALID}.</p>
     *
     * <p>As a weird special case, the source interval for rules matched after
     * EOF is unspecified.</p>
     */
     ///返回一个 Interval 对象，表示与当前子树相关联的第一个
     /// 和最后一个标记在 TokenStream 中的索引。
    virtual misc::Interval getSourceInterval() = 0;

    ParseTreeType getTreeType() const { return _treeType; }

  protected:
    explicit ParseTree(ParseTreeType treeType) : _treeType(treeType) {}

  private:
      ///terminal error rule
    const ParseTreeType _treeType;
  };

  // A class to help managing ParseTree instances without the need of a shared_ptr.
  class ANTLR4CPP_PUBLIC ParseTreeTracker {
  public:
      ///用于创建特定类型的ParseTree实例。
      /// 这个方法确保创建的实例是ParseTree的派生类，并将新创建的实例添加到一个内部向量中以便跟踪
    template<typename T, typename ... Args>
    T* createInstance(Args&& ... args) {
      static_assert(std::is_base_of<ParseTree, T>::value, "Argument must be a parse tree type");
      ///调用例如ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
      T* result = new T(args...);
      _allocated.push_back(result);
      return result;
    }
    ///清理所有已分配的 ParseTree 实例，通过删除它们来释放内存
    void reset() {
      for (auto * entry : _allocated)
        delete entry;
      _allocated.clear();
    }

  private:
      ///ParseTree * 类型的向量，用于存储所有通过 createInstance 方法创建的 ParseTree 实例
    std::vector<ParseTree *> _allocated;
  };


} // namespace tree
} // namespace antlr4
